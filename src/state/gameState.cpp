#include "gameState.h"
#include "GameSettings.h"
#include "score.h"
#include <chrono>
#include <iostream>

namespace data {
std::string Game;
std::string Map;
std::string Player;
} // namespace data

GameState::GameState(StateStack &stack)
    : State(stack), speed(0.0f), count(0), start(false), over(false), virtualScore(0), isHighScore(0),
      highScoreTimer(0.0f), HighScoreTrigger(3), timeRain(0.0f) {
    map = new Map(speed);
    player = new Player(1512.0 / 2 - 82 / 2, 982.0 - 2 * settings::GRID_SIZE.second, speed, Textures::ID::SKIN_FULL);
    pauseButton = &TextureHolder::getHolder().get(Textures::PAUSE_BUTTON);

    HideCursor();
    rain.setState(false);

    customFont = LoadFont("./font/River Adventurer.ttf");
    customFont1 = LoadFont("font/Noot Regular.woff.ttf");
    collisionSound = LoadSound("image/Sound/hitbox.wav");
    jumpSound = LoadSound("image/Sound/jump.wav");
    SetSoundVolume(collisionSound, 0.5f);

    if (data::Game != "") {
        this->loadSerializedData(data::Game, data::Map, data::Player);
        data::Game = "";
        data::Map = "";
        data::Player = "";
    }
}

GameState::~GameState() {
    delete map;
    delete player;
    UnloadFont(customFont);
    UnloadFont(customFont1);
    UnloadSound(collisionSound);
    UnloadSound(jumpSound);
    ShowCursor();
}

void GameState::draw() {
    // static int i = 0;
    // if(i++ == 0)
    //     std::cout << "GameState draw called" << std::endl;
    ClearBackground(WHITE);
    map->draw();
    player->draw();

    if (rain.getState() == 1) {
        rain.update(settings::SCREEN_WIDTH, settings::SCREEN_HEIGHT);
        rain.drawTo();
    }
    //std::cout << map->getSpeed() << std::endl;
    // Draw the regular score
    if (highScoreTimer >= 1.0f) {
        // Get the width of the existing high score text
        float highScoreTextWidth =
            MeasureTextEx(customFont,
                          ("High Score: " + std::to_string(HighScore::getHighScoreManager().getCurrentScore())).c_str(),
                          40,
                          2)
                .x;

        // Calculate the position to center "New High Score!!!" under the existing high score
        float newX = 650 + (highScoreTextWidth / 2) - (MeasureTextEx(customFont1, "New High Score!!!", 40, 2).x / 2);
        float newY = 55;
        // Draw "New High Score!!!" centered under the existing high score
        DrawTextEx(customFont1, "New High Score!!!", Vector2{newX, newY}, 40, 2, WHITE);

        highScoreTimer -= 0.05f;
    }
    if (HighScoreTrigger >= 3) {
        DrawTextEx(customFont,
                   ("Score: " + std::to_string(HighScore::getHighScoreManager().getCurrentScore())).c_str(),
                   Vector2{650, 10},
                   40,
                   2,
                   YELLOW);
    } else {
        DrawTextEx(customFont,
                   ("High Score: " + std::to_string(HighScore::getHighScoreManager().getCurrentScore())).c_str(),
                   Vector2{650, 10},
                   40,
                   2,
                   YELLOW);
    }
}


void GameState::update() {
    // static int i = 0;
    // if(i++ == 0)
    //     std::cout << "GameState update called" << std::endl;
    if (!player->getMoving())
        player->setMoving(true);

    if (start && !over)
        map->update();
    if (over)
        player->setSpeed(0.0f, 0.0f);
    player->update();
    if (rain.getState() == -1){
        rain.setState(1);
    }
    timeRain += GetFrameTime();
    if (timeRain > 10.0f){
        timeRain = 0.0f;
        if (rain.getState() == 0){
            rainSetupFunction();
        }else{
            rain.setState(0);
            float tmp = map->getSpeed();
            map->setSpeed(tmp / 3);
            player->setMapSpeed(tmp / 3);
        }
    }
}
void GameState::rainSetupFunction() {
    bool generateRain = (rand() % 10) < 4;
    if (generateRain) {
        rain.setState(1);
        float tmp = map->getSpeed();
        map->setSpeed(tmp * 3);
        player->setMapSpeed(tmp * 3);
    } else {
        rain.setState(0);
    }
}


// void GameState::init() {
//     nextState = nullptr;
// }

void GameState::handleEvents() {
    if (over) {
        requestStackPush(States::ID::GameOver);
        rain.setState(0);
        HighScore::getHighScoreManager().updateHighestScore();
        // for (int i = 1; i <= 3; i++)
        // std::cout << HighScore::getHighScoreManager().getHighestScore(i) << std::endl;
    } else if (!over) {
        setMapSpeed();
        if (start) {
            checkOutOfScreen();
            checkCollision();
            checkPlayerAlive();
            handleInput();
        }
    } else
        checkEndOfGame();
}

void GameState::checkOutOfScreen() {
    if (player->getPosition().second > 982.0f){
        player->setIsAlive(false);
        PlaySound(collisionSound);
    }
}

void GameState::checkCollision() {
    if (map->CheckCollisionPlayer(player->getBoxCollision())){
        player->setIsAlive(false);
        PlaySound(collisionSound);
    }
}

void GameState::setMapSpeed() {
    if (player->getPosition().second < 982.0f / 2.0f) {
        float deltaSpeed = (982.0f / 2.0f - player->getPosition().second) / 300 * 0.2f;
        speed += deltaSpeed;
        map->setSpeed(speed);
        player->setMapSpeed(speed);
        // player->setSkin(Textures::ID::SKIN_2);
    } else {
        if (speed != 0.0f && speed != 1.2f) {
            speed = 1.2f;
            map->setSpeed(speed);
            player->setMapSpeed(speed);
            // player->setSkin(Textures::ID::SKIN_1);
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
    if (GetTime() - count >= 0.1f &&
        !(player->getPosition() != player->getTargetPosition())) // Set delay between key presses and movement
    {
        if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {
            count = GetTime();
            player->move(Player::Direction::UP);
            PlaySound(jumpSound);
            virtualScore++;
            if (virtualScore > HighScore::getHighScoreManager().getCurrentScore()) {
                HighScore::getHighScoreManager().setCurrentScore(virtualScore);
            }
            // std::cerr << highScore << std::endl;
        } else if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {
            count = GetTime();
            player->move(Player::Direction::DOWN);
            PlaySound(jumpSound);
            virtualScore--;
            if (virtualScore > HighScore::getHighScoreManager().getCurrentScore()) {
                HighScore::getHighScoreManager().setCurrentScore(virtualScore);
            }
        } else if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) {
            count = GetTime();
            PlaySound(jumpSound);
            player->move(Player::Direction::LEFT);
        } else if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) {
            count = GetTime();
            PlaySound(jumpSound);
            player->move(Player::Direction::RIGHT);
        }

        if (HighScoreTrigger > 0 && HighScore::getHighScoreManager().getCurrentScore() >
                                        HighScore::getHighScoreManager().getHighestScore(HighScoreTrigger)) {
            HighScoreTrigger--;
            highScoreTimer = 4.0f;
            //std::cout << HighScoreTrigger << std::endl;
            //HighScore::getHighScoreManager().updateHighestScore();
        }
    }

    if (IsKeyPressed(KEY_P)) {
        requestStackPush(States::ID::Pause);
        if (rain.getState() == 1) rain.setState(-1);
        player->setMoving(false);
    }

    if (IsKeyPressed(KEY_B)) {
        requestStackPop();
        if (rain.getState() == 1) rain.setState(0);
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

// [gameData] = [seed] [highScore] [score]
std::string GameState::serializeData() {
    std::string gameData = std::to_string(seed) + " " +
                           std::to_string(HighScore::getHighScoreManager().getCurrentScore()) + " " +
                           std::to_string(speed);

    std::string mapData = map->serializeData();
    std::string playerData = player->serializeData();

    return "[GAME]\n" + gameData + "\n[MAP]\n" + mapData + "\n[PLAYER]\n" + playerData;
}

void GameState::loadSerializedData(const std::string &gameData,
                                   const std::string &mapData,
                                   const std::string &playerData) {
    std::stringstream ss(gameData);
    int highScore;

    ss >> seed >> highScore >> speed;
    speed = 0.0f;
    HighScore::getHighScoreManager().setCurrentScore(highScore);

    map->loadSerializedData(mapData);
    player->loadSerializedData(playerData);
}