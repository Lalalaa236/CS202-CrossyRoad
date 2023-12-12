#include "gameState.h"
#include"GameSettings.h"
#include <iostream>
#include <chrono>
const float ZOOM_DURATION = 3.5f;
GameState::GameState(StateStack& stack) :
    State(stack), speed(0.0f), count(0), start(false), over(false), score(0),isHighScore(0),highScoreZoomTimer(0.0f),HighScoreTrigger(false),highScore(0),timeSinceLastRain(0.0f)
{
    map = new Map(speed);
    player = new Player(1512.0 / 2 - 82 / 2, 982.0 - 2 * settings::GRID_SIZE.second, speed, Textures::ID::SKIN_FULL);
    pauseButton = &TextureHolder::getHolder().get(Textures::PAUSE_BUTTON);
    HideCursor();
    rain.setState(false);
    customFont = LoadFont("./font/River Adventurer.ttf");
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
        rain.update(settings::SCREEN_WIDTH,settings::SCREEN_HEIGHT);
        rain.drawTo();
    }

    if (highScoreZoomTimer > 0.0f) {
    float scaleFactor = 1.0f + (1.0f - highScoreZoomTimer / ZOOM_DURATION) * 0.5f;
    float fontSize = 100 * scaleFactor; 
    Vector2 centerPosition = {
        static_cast<float>(settings::SCREEN_WIDTH) / 2 - MeasureTextEx(customFont, "High Score", fontSize, 2).x / 2,
        static_cast<float>(settings::SCREEN_HEIGHT) / 2 - fontSize / 2
    };
    DrawTextEx(customFont, ("High Score"),
               centerPosition,
               fontSize,
               2,
               Fade(RED, highScoreZoomTimer / ZOOM_DURATION));

    highScoreZoomTimer -= GetFrameTime();
    } else {
    // Draw the regular score
        if (!HighScoreTrigger){
            DrawTextEx(customFont, ("Score: " + std::to_string(score)).c_str(),
                    Vector2{650, 10},
                    40,
                    2,
                    RED);
        }else{
              DrawTextEx(customFont, ("High Score: " + std::to_string(score)).c_str(),
                    Vector2{650, 10},
                    40,
                    2,
                    RED);
        }
            
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
    if(over)
        player->setSpeed(0.0f, 0.0f);
    player->update();
    timeSinceLastRain += GetFrameTime();

    // Check if it's time to trigger rain
    if (timeSinceLastRain >= 10.0f) {
        // Reset the timer
        timeSinceLastRain = 0.0f;

        // Trigger random rain effect
        rainSetupFunction();
    }

    
}
void GameState::rainSetupFunction() {
     bool generateRain = (rand() % 10) < 3;
     if (generateRain) {
        rain.setState(true);
    } else {
        rain.setState(false);
    }
}


// void GameState::init() {
//     nextState = nullptr;
// }

void GameState::handleEvents()
{
    if (over){
        requestStackPush(States::ID::GameOver);
    }else
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
        // player->setSkin(Textures::ID::SKIN_2);
    }
    else {
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
    if (GetTime() - count >= 0.2f && player->getPosition() == player->getTargetPosition()) // Set delay between key presses and movement
    {
        if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
        {
            count = GetTime();
            player->move(Player::Direction::UP);

            score++;
            // std::cerr << highScore << std::endl;
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

        if (score > highScore){
            if (!HighScoreTrigger) highScoreZoomTimer = ZOOM_DURATION;
            highScore = score;
            HighScoreTrigger = true; 
        }
    }

    if (IsKeyPressed(KEY_P))
    {
        requestStackPush(States::ID::Pause);
        player->setMoving(false);
    }

    if (IsKeyPressed(KEY_B))
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