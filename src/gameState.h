#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Map.h"
#include "Player.h"
#include "State.h"
#include "PauseState.h"

class GameState : public State {
private:
    Texture2D* pauseButton;
    Player* player;
    Map* map;
    float speed;
    float count;
    bool start;
    bool over;
    int score;
    int highScore;

    void checkOutOfScreen();
    void checkCollision();
    void setMapSpeed();
    void checkPlayerAlive();
    void handleInput();
    void checkEndOfGame();

public:
    GameState(StateStack& stack);
    // GameState(const GameState& gameState);
    // GameState& operator=(const GameState& gameState);
    ~GameState();

    void draw() override;
    void update() override;
    bool shouldPop() const override;
    // void init() override;
    void handleEvents() override;
};

#endif