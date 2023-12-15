#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "GameSettings.h"
#include "Map.h"
#include "PauseState.h"
#include "Player.h"
#include "Rain.h"
#include "saveState.h"
#include "State.h"

class SaveState;

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
    unsigned long long seed;
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

    std::string serializeData();
    void loadSerializedData(std::string gameData, std::string mapData, std::string playerData);

    friend class SaveState;
};

#endif