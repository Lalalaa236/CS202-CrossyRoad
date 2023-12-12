#include "instructionState.h"

InstructionState::InstructionState(StateStack &stack) : State(stack) {
    background = &TextureHolder::getHolder().get(Textures::BACKGROUND_MENU);
    instructionImages[0] = &TextureHolder::getHolder().get(Textures::INSTRUCTION_1);
    instructionImages[1] = &TextureHolder::getHolder().get(Textures::INSTRUCTION_2);
    closeButton = &TextureHolder::getHolder().get(Textures::CLOSE_BUTTON);
    nextButton = &TextureHolder::getHolder().get(Textures::NEXT_BUTTON);
    prevButton = &TextureHolder::getHolder().get(Textures::PREVIOUS_BUTTON);
    currentImage = 0;
}

InstructionState::~InstructionState() {
}

void InstructionState::handleEvents() {
    // Next and previous button
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePosition = GetMousePosition();
        if (CheckCollisionPointRec(mousePosition, {1090, 500, nextButton->width * 1.0f, nextButton->height * 1.0f})) {
            currentImage++;
            if (currentImage > 1)
                currentImage = 0;
        }
        if (CheckCollisionPointRec(mousePosition, {300, 500, prevButton->width * 1.0f, prevButton->height * 1.0f})) {
            currentImage--;
            if (currentImage < 0)
                currentImage = 1;
        }
    }

    // Close button
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePosition = GetMousePosition();
        if (CheckCollisionPointRec(mousePosition, {1113, 202, closeButton->width * 1.0f, closeButton->height * 1.0f})) {
            // shouldPopState = true;
            requestStackPop();
            requestStackPush(States::ID::Menu);
        }
    }
}

void InstructionState::update() {
}

void InstructionState::draw() {
    float scaleWidth = (float)GetScreenWidth() / background->width;
    float scaleHeight = (float)GetScreenHeight() / background->height;
    ClearBackground(RAYWHITE);
    // Draw background image
    DrawTexturePro(*background,
                   {0, 0, float(background->width), float(background->height)},
                   {0, 0, background->width * scaleWidth, background->height * scaleHeight},
                   {0, 0},
                   0,
                   WHITE);

    if (currentImage == 0) {
        DrawTexture(*instructionImages[0], 319, 81, WHITE);
        DrawTexture(*nextButton, 1090, 500, WHITE);
        DrawTexture(*closeButton, 1113, 202, WHITE);
    } else {
        DrawTexture(*instructionImages[1], 319, 81, WHITE);
        DrawTexture(*prevButton, 300, 500, WHITE);
        DrawTexture(*closeButton, 1113, 202, WHITE);
    }
}
