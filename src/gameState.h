#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "GameSettings.h"
#include "Map.h"
#include "Player.h"
#include "State.h"
#include "PauseState.h"
#include "Rain.h"
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
    Rain rain;

    void checkOutOfScreen();
    void checkCollision();
    void setMapSpeed();
    void checkPlayerAlive();
    void handleInput();
    void checkEndOfGame();

public:
    GameState(StateStack& stack);
    ~GameState();

    void draw() override;
    void update() override;
    void handleEvents() override;
};

#endif