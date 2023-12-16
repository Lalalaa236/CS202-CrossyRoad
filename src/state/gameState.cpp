#include "gameState.h"
#include"GameSettings.h"
#include"score.h"
#include <iostream>
#include <chrono>

GameState::GameState(StateStack& stack) :
    State(stack), speed(0.0f), count(0), start(false), over(false), virtualScore(0),isHighScore(0),highScoreTimer(0.0f),HighScoreTrigger(3),timeSinceLastRain(0.0f)
{
    map = new Map(speed);
    player = new Player(1512.0 / 2 - 82 / 2, 982.0 - 2 * settings::GRID_SIZE.second, speed, Textures::ID::SKIN_FULL);
    pauseButton = &TextureHolder::getHolder().get(Textures::PAUSE_BUTTON);
    HideCursor();
    rain.setState(false);
    customFont = LoadFont("./font/River Adventurer.ttf");
    customFont1 = LoadFont("font/Noot Regular.woff.ttf");
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
    // Draw the regular score
     if (highScoreTimer >= 1.0f) {
            // Get the width of the existing high score text
            float highScoreTextWidth = MeasureTextEx(customFont, ("High Score: " + std::to_string(HighScore::getHighScoreManager().getCurrentScore())).c_str(), 40, 2).x;

            // Calculate the position to center "New High Score!!!" under the existing high score
            float newX = 650 + (highScoreTextWidth / 2) - (MeasureTextEx(customFont1,"New High Score!!!", 40,2).x / 2);
            float newY = 55; 
            // Draw "New High Score!!!" centered under the existing high score
            DrawTextEx(customFont1, "New High Score!!!",
                Vector2{newX, newY},
                40,
                2,
                WHITE);

            highScoreTimer -= 0.05f;
     }
    if (HighScoreTrigger >= 3){
        DrawTextEx(customFont, ("Score: " + std::to_string(HighScore::getHighScoreManager().getCurrentScore())).c_str(),
            Vector2{650, 10},
            40,
            2,
            YELLOW);
    }else{
        DrawTextEx(customFont, ("High Score: " + std::to_string(HighScore::getHighScoreManager().getCurrentScore())).c_str(),
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
    if(over)
        player->setSpeed(0.0f, 0.0f);
    player->update();
    timeSinceLastRain += GetFrameTime();

    // Check if it's time to trigger rain
    if (timeSinceLastRain >= 10.0f) {
        // Reset the timer
        timeSinceLastRain = 0.0f;
        float tmp = map->getSpeed();
        map->setSpeed(tmp*3);
        player->setMapSpeed(tmp*3);

        // Trigger random rain effect
        rainSetupFunction();
    }

    
}
void GameState::rainSetupFunction() {
    bool generateRain = (rand() % 10) < 3;
    if (generateRain) {
        rain.setState(true);
        float tmp = map->getSpeed();
        map->setSpeed(tmp/3);
        player->setMapSpeed(tmp/3);
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
        rain.setState(false);
        HighScore::getHighScoreManager().updateHighestScore();
        // for (int i = 1; i <= 3; i++)
        // std::cout << HighScore::getHighScoreManager().getHighestScore(i) << std::endl;
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

            virtualScore++;
            if (virtualScore > HighScore::getHighScoreManager().getCurrentScore()){
                HighScore::getHighScoreManager().setCurrentScore(virtualScore);
            }
            // std::cerr << highScore << std::endl;
        }
        else if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {
            count = GetTime();
            player->move(Player::Direction::DOWN);

            virtualScore--;
            if (virtualScore > HighScore::getHighScoreManager().getCurrentScore()){
                HighScore::getHighScoreManager().setCurrentScore(virtualScore);
            }
        }
        else if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) {
            count = GetTime();
            player->move(Player::Direction::LEFT);
        }
        else if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) {
            count = GetTime();
            player->move(Player::Direction::RIGHT);
        }

        if (HighScoreTrigger > 0 && HighScore::getHighScoreManager().getCurrentScore() > HighScore::getHighScoreManager().getHighestScore(HighScoreTrigger)){
            HighScoreTrigger--;
            highScoreTimer = 4.0f;
            //std::cout << HighScoreTrigger << std::endl;
            //HighScore::getHighScoreManager().updateHighestScore();
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