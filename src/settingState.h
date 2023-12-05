#pragma once
#include "Game.h"
#include "State.h"
#include "raylib.h"

class Game;
class settingState : public State {
public:
    settingState(Game &game);
    ~settingState();
    void init() override;

    bool shouldPop() const override;
    void handleEvents() override;

    void setDot(float volume);

    void update() override;
    void draw() override;

private:
    Game &game;
    Texture2D *background;
    Texture2D *settingBoard;
    Texture2D *closeButton;
    Texture2D *sound[5];
    Vector2 dotPosition;
};