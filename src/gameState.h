#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Map.h"
#include "Player.h"
#include "State.h"

class GameState : public State {
private:
    Player* player;
    Map* map;
    float speed;
    float count;
    bool start;
    bool over;

    void checkOutOfScreen();
    void checkCollision();
    void setMapSpeed();
    void checkPlayerAlive();
    void handleInput();
    void checkEndOfGame();

public:
    GameState();
    GameState(const GameState& gameState);
    GameState& operator=(const GameState& gameState);
    ~GameState();

    void draw() override;
    void update() override;
    bool shouldPop() const override;
    void init() override;
    void handleEvents() override;
};

#endif