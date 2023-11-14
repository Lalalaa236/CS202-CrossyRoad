#pragma once
#include"raylib.h"
#include"State.h"

class MenuState : public State {
public:
    MenuState();
    void handleEvents() override;
    void update() override;
    void draw() const override;
    ~MenuState();
    bool shouldPop() const override;
private:
    Texture2D background;
    Texture2D button[6];
    Texture2D name;
};

