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
    State* getNextState() const;
    bool shouldPop() const override;
private:
    State* nextState = nullptr;
    Texture2D background;
    Texture2D button[6];
    Texture2D name;
};