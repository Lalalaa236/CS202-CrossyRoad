#include "gameState.h"
#include "random.h"
#include <chrono>
#include <iostream>
#include <sstream>

GameState::GameState(StateStack& stack) : State(stack), speed(0.0f), count(0), start(false), over(false), score(0), highScore(0) {
    map = new Map(speed);
    player = new Player(1512.0 / 2 - 82 / 2, 982.0 - 2 * settings::GRID_SIZE.second, speed, Textures::ID::SKIN_FULL);
    pauseButton = &TextureHolder::getHolder().get(Textures::PAUSE_BUTTON);

    // Set random seed to generate random map and obstacles
    Random::getInstance().setRandomSeed();
    seed = Random::getInstance().getSeed();

    rain.setState(false);

    HideCursor();
    // std::cout << "GameState constructor called" << std::endl;
}

GameState::~GameState() {
    delete map;
    delete player;
    ShowCursor();
}

void GameState::draw() {
    // static int i = 0;
    // if(i++ == 0)
    //     std::cout << "GameState draw called" << std::endl;
    ClearBackground(WHITE);
    map->draw();
    player->draw();

    if (rain.getState()) {
        rain.update(1512, 982);
        rain.drawTo();
    }
    // player->draw();
}

void GameState::update() {
    // static int i = 0;
    // if(i++ == 0)
    //     std::cout << "GameState update called" << std::endl;
    if (!player->getMoving())
        player->setMoving(true);

    if (start && !over)
        map->update(highScore);

    if (over)
        player->setSpeed(0.0f, 0.0f);

    player->update();
}

// void GameState::init() {
//     nextState = nullptr;
// }

void GameState::handleEvents() {
    if (over) {
        requestStackPush(States::ID::GameOver);
    }
    else if (!over) {
        setMapSpeed();
        if (start) {
            checkOutOfScreen();
            checkCollision();
            checkPlayerAlive();
            handleInput();
        }
    }
    else
        checkEndOfGame();
}

void GameState::checkOutOfScreen() {
    if (player->getPosition().second > 982.0f)
        player->setIsAlive(false);
}

void GameState::checkCollision() {
    if (map->CheckCollisionPlayer(player->getBoxCollision()))
        player->setIsAlive(false);
}

void GameState::setMapSpeed() {
    if (player->getPosition().second < 982.0f / 2.0f) {
        float deltaSpeed = (982.0f / 2.0f - player->getPosition().second) / 300 * 0.2f;
        speed += deltaSpeed;
        map->setSpeed(speed);
        player->setMapSpeed(speed);
    }
    else {
        if (speed != 0.0f && speed != 1.2f) {
            speed = 1.2f;
            map->setSpeed(speed);
            player->setMapSpeed(speed);
        }
    }

    if (speed == 0.0f &&
        (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W) || IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S) ||
            IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A) || IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D))) {
        speed = 1.2f;
        map->setSpeed(speed);
        player->setMapSpeed(speed);
        start = true;
    }
}

void GameState::checkPlayerAlive() {
    if (!player->getIsAlive()) {
        over = true;
        speed = 0.0f;

        map->setSpeed(speed);
        player->setMapSpeed(speed);
    }
}

void GameState::handleInput() {
    if (GetTime() - count >= 0.2f &&
        player->getPosition() == player->getTargetPosition()) // Set delay between key presses and movement
    {
        if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {
            count = GetTime();
            player->move(Player::Direction::UP);

            score++;
            if (score > highScore)
                highScore = score;
        }
        else if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {
            count = GetTime();
            player->move(Player::Direction::DOWN);

            score--;
        }
        else if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) {
            count = GetTime();
            player->move(Player::Direction::LEFT);
        }
        else if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) {
            count = GetTime();
            player->move(Player::Direction::RIGHT);
        }
    }

    if (IsKeyPressed(KEY_P)) {
        requestStackPush(States::ID::Pause);
        player->setMoving(false);
    }

    if (IsKeyPressed(KEY_B)) {
        requestStackPop();
        requestStackPush(States::ID::Menu);
    }
}

void GameState::checkEndOfGame() {
    if (IsKeyPressed(KEY_B)) {
        requestStackPop();
        requestStackPush(States::ID::Menu);
    }

    if (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT))
        ShowCursor();
    else
        HideCursor();
}


std::string GameState::serializeData() {
    std::string serializd_data = "";

    serializd_data += std::to_string(seed) + "\n";
    serializd_data += std::to_string(highScore) + "\n";
    serializd_data += std::to_string(score) + "\n";
    serializd_data += std::to_string(player->getPosition().first) + "\n";
    serializd_data += std::to_string(player->getPosition().second) + "\n";
    serializd_data += std::to_string(player->getTargetPosition().first) + "\n";
    serializd_data += std::to_string(player->getTargetPosition().second) + "\n";

    serializd_data += std::to_string(player->getSpeed().first) + "\n";
    serializd_data += std::to_string(player->getSpeed().second) + "\n";
    serializd_data += std::to_string(player->getFrameCount()) + "\n";
    serializd_data += std::to_string(settings::CURRENT_SKIN) + "\n";

    return serializd_data;
}

void GameState::loadSerializedData(std::string serialized_data) {
    std::string line;
    std::stringstream ss(serialized_data);

    float x, y;

    std::getline(ss, line);
    seed = std::stoull(line);

    std::getline(ss, line);
    highScore = std::stoi(line);

    std::getline(ss, line);
    score = std::stoi(line);

    std::getline(ss, line);
    x = std::stof(line);
    std::getline(ss, line);
    y = std::stof(line);
    player->setPosition(x, y);

    std::getline(ss, line);
    x = std::stof(line);
    std::getline(ss, line);
    y = std::stof(line);
    player->setTargetPosition(x, y);

    std::getline(ss, line);
    x = std::stof(line);
    std::getline(ss, line);
    y = std::stof(line);
    player->setSpeed(x, y);

    std::getline(ss, line);
    player->setFrameCount(std::stoi(line));

    std::getline(ss, line);
    settings::CURRENT_SKIN = std::stoi(line);
}
