#pragma once
#include "State.h"
#include "raylib.h"

class highScoreState : public State {
public:
    highScoreState(StateStack& stack);
    ~highScoreState();

    // void init() override;

    bool shouldPop() const override;
    void handleEvents() override;

    void draw() override;
    void update() override;

private:
    Texture2D *background;
    Texture2D *highScoreBoard;
    Texture2D *closeButton;
};