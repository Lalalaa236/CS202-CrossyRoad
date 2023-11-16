#pragma once
#include"State.h"
#include"raylib.h"

class settingState : public State{
public:
    settingState();
    void handleEvents() override;
    void update() override;
    void draw() const override;
    ~settingState();
    bool shouldPop() const override;
    void init() override;
private:
    Texture2D* background;
    Texture2D* settingBoard;
    Texture2D* closeButton;
    Texture2D* sound[5];
};