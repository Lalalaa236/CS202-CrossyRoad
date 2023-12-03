#include "gameState.h"
#include <iostream>
#include <limits>

GameState::GameState() : speed(0.0f), count(0), start(false), over(false) {
    map = new Map(speed);
    player = new Player(1512.0 / 2 - 82 / 2, 982.0 - settings::GRID_SIZE.second, speed);
    shouldPopState = false;
    HideCursor();
    // std::cout << "GameState constructor called" << std::endl;
}

GameState::GameState(const GameState& gameState) {
    map = new Map(*gameState.map);
    player = new Player(*gameState.player);
    speed = gameState.speed;
    count = gameState.count;
    start = gameState.start;
    over = gameState.over;
    shouldPopState = gameState.shouldPopState;
}

GameState& GameState::operator=(const GameState& gameState) {
    if (this == &gameState)
        return *this;

    delete map;
    delete player;
    map = new Map(*gameState.map);
    player = new Player(*gameState.player);
    speed = gameState.speed;
    count = gameState.count;
    start = gameState.start;
    over = gameState.over;
    shouldPopState = gameState.shouldPopState;

    return *this;
}

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
    BeginDrawing();
    ClearBackground(RAYWHITE);
    map->draw();
    player->draw();
    EndDrawing();
    // player->draw();
}

void GameState::update() {
    // static int i = 0;
    // if(i++ == 0)
    //     std::cout << "GameState update called" << std::endl;
    if (start && !over)
        map->update();
    player->update();
    // player->update();
}

void GameState::init() {
    nextState = nullptr;
}

void GameState::handleEvents() {
    if (!over) {
        setMapSpeed();
        if (start) {
            checkOutOfScreen();
            checkCollision();
            checkPlayerAlive();
            handleInput();
        }
    }
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
    if (player->getPosition().second < 982.0f / 2) {
        float deltaSpeed = (982 / 2 - (int)player->getPosition().second) / 300 * 0.2f;
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

void GameState::handleInput()
{
    if (GetTime() - count > 0.15f)
    {
        if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
        {
            count = GetTime();
            player->move(Player::Direction::UP);
        }
        else if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {
            count = GetTime();
            player->move(Player::Direction::DOWN);
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
}

void GameState::checkEndOfGame() {
    if (IsKeyPressed(KEY_P))
        shouldPopState = true;
    if (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT))
        ShowCursor();
    else
        HideCursor();
}