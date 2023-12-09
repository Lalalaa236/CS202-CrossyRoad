#include "skinState.h"
#include <iostream>

void SkinState::setAnimation(int skinIndex, Textures::ID skinID) {
    animation[skinIndex].setAnimation(skinID, 4, 4.0f);
}

SkinState::SkinState(StateStack& stack) 
: State(stack) 
{
    shouldPopState = false;
    skinBoard = &TextureHolder::getHolder().get(Textures::SKIN_TABLE);
    background = &TextureHolder::getHolder().get(Textures::BACKGROUND_MENU);
    closeButton = &TextureHolder::getHolder().get(Textures::CLOSE_BUTTON);
    nextButton = &TextureHolder::getHolder().get(Textures::NEXT_BUTTON);
    prevButton = &TextureHolder::getHolder().get(Textures::PREVIOUS_BUTTON);
    setButton = &TextureHolder::getHolder().get(Textures::CONFIRM_BUTTON);

    setAnimation(0, Textures::SKIN_1_DOWN);
    setAnimation(1, Textures::SKIN_2_DOWN);

    // Placeholder
    setAnimation(2, Textures::SKIN_1_DOWN);
    setAnimation(3, Textures::SKIN_2_DOWN);
    setAnimation(4, Textures::SKIN_1_DOWN);

    currentSkin = 0;
}

SkinState::~SkinState() {
}

// void SkinState::init() {
// }

bool SkinState::shouldPop() const {
    return shouldPopState;
}

void SkinState::handleEvents() {
    // Next and previous button
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePosition = GetMousePosition();
        if (CheckCollisionPointRec(mousePosition, {1090, 500, nextButton->width * 1.0f, nextButton->height * 1.0f})) {
            currentSkin++;
            if (currentSkin > 4)
                currentSkin = 0;
        }
        if (CheckCollisionPointRec(mousePosition, {300, 500, prevButton->width * 1.0f, prevButton->height * 1.0f})) {
            currentSkin--;
            if (currentSkin < 0)
                currentSkin = 4;
        }
    }

    // Close button
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePosition = GetMousePosition();
        if (CheckCollisionPointRec(mousePosition, {1113, 202, closeButton->width * 1.0f, closeButton->height * 1.0f})) {
            shouldPopState = true;
        }
    }

    // Set button
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePosition = GetMousePosition();
        if (CheckCollisionPointRec(mousePosition, {680, 700, setButton->width * 1.0f, setButton->height * 1.0f})) {
            // Set the skin to player
            switch (currentSkin) {
            case 0: // Skin 1

                break;
            case 1: // Skin 2
                break;
            case 2: // Skin 3
                break;
            case 3: // Skin 4
                break;
            case 4: // Skin 5
                break;
            }

            // Pop the state
            // shouldPopState = true;
            requestStackPop();
            requestStackPush(States::ID::Menu);
        }
        if (CheckCollisionPointRec(mousePosition, {1113, 202, closeButton->width * 1.0f, closeButton->height * 1.0f})) {
            requestStackPop();
            requestStackPush(States::ID::Menu);
        }
    }
}

void SkinState::update() {
}

void SkinState::draw() {
    float scaleWidth = (float)GetScreenWidth() / background->width;
    float scaleHeight = (float)GetScreenHeight() / background->height;

    ClearBackground(RAYWHITE);
    DrawTexturePro(*background,
                   {0, 0, float(background->width), float(background->height)},
                   {0, 0, background->width * scaleWidth, background->height * scaleHeight},
                   {0, 0},
                   0,
                   WHITE);

    DrawTexture(*skinBoard, 305, 79, WHITE);
    // DrawTexture(*skin[currentSkin], 500, 500, WHITE);

    // Draw the animation of skin
    animation[currentSkin].elapsedTime += GetFrameTime();
    if (animation[currentSkin].elapsedTime >= 1.0f / animation[currentSkin].frameRate) {
        animation[currentSkin].currentFrame++;
        animation[currentSkin].elapsedTime = 0.0f;
        if (animation[currentSkin].currentFrame > animation[currentSkin].numFrames - 1) {
            animation[currentSkin].currentFrame = 0;
        }
    }

    DrawTextureRec(animation[currentSkin].spriteSheet,
                   animation[currentSkin].frameRectangles[animation[currentSkin].currentFrame],
                   {620, 400},
                   WHITE);

    // Draw button
    DrawTexture(*nextButton, 1097, 500, WHITE);
    DrawTexture(*prevButton, 280, 500, WHITE);
    DrawTexture(*closeButton, 1087, 202, WHITE);
    DrawTexture(*setButton, 680, 700, WHITE);
}