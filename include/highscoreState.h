#pragma once
#include "State.h"
#include "raylib.h"

class highScoreState : public State {
public:
    highScoreState(StateStack& stack);
    ~highScoreState();

    void draw() override;
    void update() override;
    void handleEvents() override;

private:
    Texture2D *background;
    Texture2D *highScoreBoard;
    Texture2D *closeButton;
    Texture2D *leaderBoard;
    int score[3];
    Font customFont;
};