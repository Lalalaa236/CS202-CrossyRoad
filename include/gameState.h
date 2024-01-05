#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "GameSettings.h"
#include "Map.h"
#include "PauseState.h"
#include "Player.h"
#include "SpecialEffect.h"
#include "saveState.h"
#include "State.h"

class GameState : public State {
private:
    Texture2D* pauseButton;
    Player* player;
    Map* map;

    unsigned long long seed;
    float speed;
    float count;
    bool start;
    bool over;
    int virtualScore;
    std::unique_ptr<SpecialEffect> effect;
    Font customFont;
    Font customFont1;
    int isHighScore;
    float highScoreTimer; 
    int HighScoreTrigger; 
    float timeRain;
    Sound collisionSound;
    Sound jumpSound;
    void checkOutOfScreen();
    void checkCollision();
    void setMapSpeed();
    void checkPlayerAlive();
    void handleInput();
    void checkEndOfGame();
    void rainSetupFunction();

public:
    GameState(StateStack& stack);
    ~GameState();

    void draw() override;
    void update() override;
    void handleEvents() override;
    
    std::string serializeData();
    void loadSerializedData(const std::string& gameData, const std::string& mapData, const std::string& playerData);
};

#endif
