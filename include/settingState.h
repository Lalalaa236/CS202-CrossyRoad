#pragma once
#include "Game.h"
#include "MusicManager.h"
#include "State.h"
#include "raylib.h"

class Game;
class settingState : public State {
public:
    settingState(StateStack &stack);
    ~settingState();

    void draw() override;
    void update() override;
    void handleEvents() override;

private:
    Texture2D *background;
    Texture2D *settingBoard;
    Texture2D *closeButton;
    Texture2D *sound[5];
    Vector2 dotPosition;
};