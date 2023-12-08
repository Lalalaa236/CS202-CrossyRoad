#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Map.h"
#include "Player.h"
#include "State.h"
#include<vector>
#include"Obstacle.h"
class GameState : public State {
private:
    Player* player;
    Map* map;
    float speed;
    float count;
    bool start;
    bool over;
    Texture2D* Pausebtn;
    Texture2D* PauseBoard;
    Texture2D* closeBtn;
    void checkOutOfScreen();
    void checkCollision();
    void setMapSpeed();
    void checkPlayerAlive();
    void handleInput();
    void checkEndOfGame();
    void drawPauseBoard();
    bool isPause = false;
    std::vector<std::pair<Obstacle*,float>> Pause;

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
    void SaveCurrentState();
    void rePlay();
};

#endif