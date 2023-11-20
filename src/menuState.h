#pragma once
#include"raylib.h"
#include"State.h"

class Game;
class MenuState : public State {
public:
    MenuState(Game& game);
    void handleEvents() override;
    void update() override;
    void draw() override;
    ~MenuState();
    bool shouldPop() const override;
    void init() override;
private:
    Game& game;
    Texture2D* background;
    Texture2D* button[6];
    Texture2D* name;
};

