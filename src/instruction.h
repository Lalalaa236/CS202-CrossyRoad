#pragma once
#include "State.h"
#include "raylib.h"
#include "TextureHolder.h"

class InstructionState : public State {
public:
    InstructionState();
    ~InstructionState();

    void init() override;
    bool shouldPop() const override;

    void handleEvents() override;
    void update() override;
    void draw() override;

private:
    Texture2D* background;
    Texture2D* instructionImages[2];
    Texture2D* closeButton;
    Texture2D* nextButton;
    Texture2D* prevButton;
    int currentImage;
};
