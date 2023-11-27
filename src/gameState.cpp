#include "gameState.h"
#include <iostream>

GameState::GameState() : speed(0.0f) {
    map = new Map(speed);
    player = nullptr;
    shouldPopState = false;

    score = 0;
    highScore = 0;
    // std::cout << "GameState constructor called" << std::endl;
}

GameState::~GameState() {
    delete map;
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
    EndDrawing();
    // player->draw();
}

void GameState::update() {
    // static int i = 0;
    // if(i++ == 0)
    //     std::cout << "GameState update called" << std::endl;
    map->update();
    // player->update();
}

void GameState::init() {
    nextState = nullptr;
}

void GameState::handleEvents() {
    if (speed == 0.0f && (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))) {
        speed = 0.6f;
        map->setSpeed(speed);
    }

    if (IsKeyPressed(KEY_P))
        shouldPopState = true;
}