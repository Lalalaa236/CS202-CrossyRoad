#include "gameState.h"
#include <iostream>

GameState::GameState()
{
    map = new Map();
    player = nullptr;
    shouldPopState = false;
    std::cout << "GameState constructor called" << std::endl;
}

GameState::~GameState()
{
    delete map;
}

bool GameState::shouldPop() const
{
    return shouldPopState;
}

void GameState::draw()
{
    static int i = 0;
    if(i++ == 0)
        std::cout << "GameState draw called" << std::endl;
    BeginDrawing();
    ClearBackground(RAYWHITE);
    map->draw();
    EndDrawing();
    // player->draw();
}

void GameState::update()
{
    static int i = 0;
    if(i++ == 0)
        std::cout << "GameState update called" << std::endl;
    map->update();
    // player->update();
}

void GameState::init()
{
    nextState = nullptr;
}

void GameState::handleEvents()
{
    if(IsKeyPressed(KEY_P))
        shouldPopState = true;
}