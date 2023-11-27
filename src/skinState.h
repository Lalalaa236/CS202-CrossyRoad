#pragma once

#include "State.h"
#include "raylib.h"
#include "TextureHolder.h"

/// @brief Use to change the skin of the player
class SkinState : public State {
private:
    Texture2D* background;
    Texture2D* skinBoard;
    Texture2D* closeButton;
    Texture2D* nextButton;
    Texture2D* prevButton;

    Texture2D* skin[5];
    int currentSkin;

public:
    SkinState();
    ~SkinState();

    void init() override;
    bool shouldPop() const override;

    void handleEvents() override;
    void update() override;
    void draw() override;
};