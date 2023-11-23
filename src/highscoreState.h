#pragma once
#include"State.h"
#include"raylib.h"

class highScoreState : public State {
public:
    highScoreState();
    void handleEvents() override;
    void update() override;
    void draw() override;
    ~highScoreState();
    bool shouldPop() const override;
    void init() override;
private:
    Texture2D* background;
    Texture2D* highScoreBoard;
    Texture2D* closeButton;
};