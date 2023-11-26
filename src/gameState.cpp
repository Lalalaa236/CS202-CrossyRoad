#include "gameState.h"
#include <iostream>
#include <limits>

GameState::GameState()
: speed(0.0f)
{
    map = new Map(speed);
    player = new Player(1512.0/2 - settings::GRID_SIZE.first/2, 982.0 - settings::GRID_SIZE.second, speed);
    shouldPopState = false;
    HideCursor();
    // std::cout << "GameState constructor called" << std::endl;
}

GameState::~GameState()
{
    delete map;
    delete player;
    ShowCursor();
}

bool GameState::shouldPop() const
{
    return shouldPopState;
}

void GameState::draw()
{
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

void GameState::update()
{
    // static int i = 0;
    // if(i++ == 0)
    //     std::cout << "GameState update called" << std::endl;
    map->update();
    player->update();
    // player->update();
}

void GameState::init()
{
    nextState = nullptr;
}

void GameState::handleEvents()
{
    if(player->getPosition().second < 982.0/4)
    {
        speed = 3.6f;
        map->setSpeed(speed);
        player->setMapSpeed(speed);
    }
    else
    {
        if(speed != 0.0f && speed != 0.6f)
        {
            speed = 0.6f;
            map->setSpeed(speed);
            player->setMapSpeed(speed);
        }
    }
    if(speed == 0.0f && (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W) || IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S) || IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A) || IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)))
    {
        speed = 0.6f;
        map->setSpeed(speed);
        player->setMapSpeed(speed);
    }
    if(speed != 3.6f)
    {
        if(IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
            player->move(Player::Direction::UP);
        else if(IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
            player->move(Player::Direction::DOWN);
        else if(IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A))
            player->move(Player::Direction::LEFT);
        else if(IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D))
            player->move(Player::Direction::RIGHT);
    }
    if(IsKeyPressed(KEY_P))
        shouldPopState = true;
}