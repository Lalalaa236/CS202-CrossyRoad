#pragma once
#include"State.h"
#include"raylib.h"
#include"Game.h"

class Game;
class settingState : public State{
public:
    settingState(Game& game);
    void handleEvents() override;
    void update() override;
    void draw() override;
    ~settingState();
    bool shouldPop() const override;
    void init() override;
    void setDot(float volume);
private:
    Game& game;
    Texture2D* background;
    Texture2D* settingBoard;
    Texture2D* closeButton;
    Texture2D* sound[5];
    Vector2 dotPosition;
};