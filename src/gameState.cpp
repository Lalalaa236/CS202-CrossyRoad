#include "gameState.h"
#include <iostream>

GameState::GameState(StateStack& stack) : 
State(stack), speed(0.0f), count(0), start(false), over(false) 
{
    map = new Map(speed);
    player = new Player(1512.0 / 2 - 82 / 2, 982.0 - 2 * settings::GRID_SIZE.second, speed, Textures::ID::SKIN_1);
    shouldPopState = false;
    pauseButton = &TextureHolder::getHolder().get(Textures::PAUSE_BUTTON);
    HideCursor();
    // std::cout << "GameState constructor called" << std::endl;
}

// GameState::GameState(const GameState& gameState) {
//     map = new Map(*gameState.map);
//     player = new Player(*gameState.player);
//     speed = gameState.speed;
//     count = gameState.count;
//     start = gameState.start;
//     over = gameState.over;
//     shouldPopState = gameState.shouldPopState;
// }

// GameState& GameState::operator=(const GameState& gameState) {
//     if (this == &gameState)
//         return *this;

//     delete map;
//     delete player;
//     map = new Map(*gameState.map);
//     player = new Player(*gameState.player);
//     speed = gameState.speed;
//     count = gameState.count;
//     start = gameState.start;
//     over = gameState.over;
//     shouldPopState = gameState.shouldPopState;

//     return *this;
// }

GameState::~GameState() {
    delete map;
    delete player;
    ShowCursor();

    shouldPopState = true;
}

bool GameState::shouldPop() const {
    return shouldPopState;
}

void GameState::draw() {
    // static int i = 0;
    // if(i++ == 0)
    //     std::cout << "GameState draw called" << std::endl;
    ClearBackground(WHITE);
    map->draw();
    player->draw();
    DrawTexture(*pauseButton, 1409, 13, WHITE);
    // player->draw();
}

void GameState::update() {
    // static int i = 0;
    // if(i++ == 0)
    //     std::cout << "GameState update called" << std::endl;
    if(!player->getMoving())
        player->setMoving(true);
    if(start && !over)
        map->update();
    if(over)
        player->setSpeed(0.0f, 0.0f);

    player->update();
}

// void GameState::init() {
//     nextState = nullptr;
// }

void GameState::handleEvents()
{
    if (!over)
    {
        setMapSpeed();
        if (start)
        {
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

void GameState::setMapSpeed()
{
    if (player->getPosition().second < 982.0f / 2.0f)
    {
        float deltaSpeed = (982.0f / 2.0f - player->getPosition().second) / 300 * 0.2f;
        speed += deltaSpeed;
        map->setSpeed(speed);
        player->setMapSpeed(speed);
        player->setSkin(Textures::ID::SKIN_2);
    }
    else {
        if (speed != 0.0f && speed != 1.2f) {
            speed = 1.2f;
            map->setSpeed(speed);
            player->setMapSpeed(speed);
            player->setSkin(Textures::ID::SKIN_1);
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
    if (GetTime() - count >= 0.2f && player->getPosition() == player->getTargetPosition()) // Set delay between key presses and movement
    {
        if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
        {
            count = GetTime();
            player->move(Player::Direction::UP);

            score++;
            std::cerr << highScore << std::endl;
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

        if (score > highScore)
            highScore = score;
    }
    if(IsKeyPressed(KEY_P))
    {
        requestStackPush(States::ID::Pause);
        player->setMoving(false);
    }
    if(IsKeyPressed(KEY_B))
    {
        requestStackPop();
        requestStackPush(States::ID::Menu);
    }
}

void GameState::checkEndOfGame()
{
    if (IsKeyPressed(KEY_B))
    {
        requestStackPop();
        requestStackPush(States::ID::Menu);
    }
    if (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT))
        ShowCursor();
    else
        HideCursor();
}