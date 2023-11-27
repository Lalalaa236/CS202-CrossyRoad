#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "Player.h"
#include "Map.h"

class GameState : public State {
private:
    Player* player;
    Map* map;
    float speed;

    int score;
    int highScore;
public:
    GameState();
    ~GameState();

    void init() override;
    bool shouldPop() const override;
    void handleEvents() override;

    void update() override;
    void draw() override;
};

#endif