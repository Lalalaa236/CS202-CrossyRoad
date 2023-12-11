#pragma once
#include "State.h"
#include "TextureHolder.h"
#include "raylib.h"

class InstructionState : public State {
public:
    InstructionState(StateStack& stack);
    ~InstructionState();

    void update() override;
    void draw() override;
    void handleEvents() override;

private:
    Texture2D *background;
    Texture2D *instructionImages[2];
    Texture2D *closeButton;
    Texture2D *nextButton;
    Texture2D *prevButton;
    int currentImage;
};
