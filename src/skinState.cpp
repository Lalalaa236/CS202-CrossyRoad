#include "skinState.h"

SkinState::SkinState() {
    shouldPopState = false;
}

SkinState::~SkinState() {
}

void SkinState::init() {
    // background = &TextureHolder::getHolder().get(Textures::BACKGROUND_MENU);
    // skinBoard = &TextureHolder::getHolder().get(Textures::SKIN_BOARD);
    // closeButton = &TextureHolder::getHolder().get(Textures::CLOSE_BUTTON);
    // nextButton = &TextureHolder::getHolder().get(Textures::NEXT_BUTTON);
    // prevButton = &TextureHolder::getHolder().get(Textures::PREVIOUS_BUTTON);

    // skin[0] = &TextureHolder::getHolder().get(Textures::SKIN_1);
    // skin[1] = &TextureHolder::getHolder().get(Textures::SKIN_2);
    // skin[2] = &TextureHolder::getHolder().get(Textures::SKIN_3);
    // skin[3] = &TextureHolder::getHolder().get(Textures::SKIN_4);
    // skin[4] = &TextureHolder::getHolder().get(Textures::SKIN_5);

    // currentSkin = 0;
}

bool SkinState::shouldPop() const {
    return shouldPopState;
}

void SkinState::handleEvents() {
    // Next and previous button
    // if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    //     Vector2 mousePosition = GetMousePosition();
    //     if (CheckCollisionPointRec(mousePosition, { 1090, 500, nextButton->width * 1.0f,nextButton->height * 1.0f })) {
    //         currentSkin++;
    //         if (currentSkin > 4) currentSkin = 0;
    //     }
    //     if (CheckCollisionPointRec(mousePosition, { 300, 500, prevButton->width * 1.0f,prevButton->height * 1.0f })) {
    //         currentSkin--;
    //         if (currentSkin < 0) currentSkin = 4;
    //     }
    // }

    // Close button
    // if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    //     Vector2 mousePosition = GetMousePosition();
    //     if (CheckCollisionPointRec(mousePosition, { 1113, 202, closeButton->width * 1.0f,closeButton->height * 1.0f })) {
    //         shouldPopState = true;
    //     }
    // }
}

void SkinState::update() {

}

void SkinState::draw() {
    // float scaleWidth = (float)GetScreenWidth() / background->width;
    // float scaleHeight = (float)GetScreenHeight() / background->height;
    // BeginDrawing();
    // ClearBackground(RAYWHITE);
    // DrawTextureEx(*background, { 0,0 }, 0, scaleWidth, scaleHeight, WHITE);
    // DrawTextureEx(*skinBoard, { 0,0 }, 0, scaleWidth, scaleHeight, WHITE);
    // DrawTextureEx(*closeButton, { 1113,202 }, 0, scaleWidth, scaleHeight, WHITE);
    // DrawTextureEx(*nextButton, { 1090,500 }, 0, scaleWidth, scaleHeight, WHITE);
    // DrawTextureEx(*prevButton, { 300,500 }, 0, scaleWidth, scaleHeight, WHITE);
    // DrawTextureEx(*skin[currentSkin], { 500,300 }, 0, scaleWidth, scaleHeight, WHITE);
    // EndDrawing();
}