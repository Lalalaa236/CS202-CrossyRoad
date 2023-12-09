#pragma once
#include "State.h"
#include "raylib.h"

class Game;
class MenuState : public State {
public:
    MenuState(StateStack& stack);
    ~MenuState();

    // void init() override;

    bool shouldPop() const override;
    void handleEvents() override;

    void update() override;
    void draw() override;

private:
    // Game &game;
    Texture2D *background;
    Texture2D *button[6];
    Texture2D *name;
};
