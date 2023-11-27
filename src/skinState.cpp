#include "skinState.h"
#include <iostream>

void SkinState::drawAnimation() {
    Texture2D* skinSpriteSheet = &TextureHolder::getHolder().get(Textures::SKIN_1_UP);

    int numFrames = 4;
    float frameRate = 4.0f;

    int frameWidth = skinSpriteSheet->width / numFrames;
    int frameHeight = skinSpriteSheet->height;

    // std::cerr << frameWidth << " " << frameHeight << std::endl;

    Rectangle* frames = new Rectangle[numFrames];

    for (int i = 0; i < numFrames; i++) {
        frames[i].x = frameWidth * i;
        frames[i].y = 0;
        frames[i].width = frameWidth;
        frames[i].height = frameHeight;
    }

    animation.spriteSheet = *skinSpriteSheet;
    animation.frameRectangles = frames;
    animation.numFrames = numFrames;
    animation.frameRate = frameRate;
    animation.currentFrame = 0;
    animation.elapsedTime = 0.0f;
}

SkinState::SkinState() {
    shouldPopState = false;
}

SkinState::~SkinState() {
}

void SkinState::init() {
    background = &TextureHolder::getHolder().get(Textures::BACKGROUND_MENU);
    skinBoard = &TextureHolder::getHolder().get(Textures::SKIN_TABLE);
    closeButton = &TextureHolder::getHolder().get(Textures::CLOSE_BUTTON);
    nextButton = &TextureHolder::getHolder().get(Textures::NEXT_BUTTON);
    prevButton = &TextureHolder::getHolder().get(Textures::PREVIOUS_BUTTON);

    skin[0] = &TextureHolder::getHolder().get(Textures::SKIN_1_MAIN);
    drawAnimation();

    // skin[0] = &TextureHolder::getHolder().get(Textures::SKIN_1);
    // skin[1] = &TextureHolder::getHolder().get(Textures::SKIN_2);
    // skin[2] = &TextureHolder::getHolder().get(Textures::SKIN_3);
    // skin[3] = &TextureHolder::getHolder().get(Textures::SKIN_4);
    // skin[4] = &TextureHolder::getHolder().get(Textures::SKIN_5);

    currentSkin = 0;
}

bool SkinState::shouldPop() const {
    return shouldPopState;
}

void SkinState::handleEvents() {
    // Next and previous button
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePosition = GetMousePosition();
        if (CheckCollisionPointRec(mousePosition, { 1090, 500, nextButton->width * 1.0f,nextButton->height * 1.0f })) {
            currentSkin++;
            if (currentSkin > 4) currentSkin = 0;
        }
        if (CheckCollisionPointRec(mousePosition, { 300, 500, prevButton->width * 1.0f,prevButton->height * 1.0f })) {
            currentSkin--;
            if (currentSkin < 0) currentSkin = 4;
        }
    }

    // Close button
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePosition = GetMousePosition();
        if (CheckCollisionPointRec(mousePosition, { 1113, 202, closeButton->width * 1.0f,closeButton->height * 1.0f })) {
            shouldPopState = true;
        }
    }
}

void SkinState::update() {

}



void SkinState::draw() {
    float scaleWidth = (float)GetScreenWidth() / background->width;
    float scaleHeight = (float)GetScreenHeight() / background->height;

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTexturePro(
        *background,
        { 0, 0, float(background->width), float(background->height) },
        { 0, 0, background->width * scaleWidth, background->height * scaleHeight },
        { 0, 0 },
        0,
        WHITE
    );

    DrawTexture(*skinBoard, 319, 81, WHITE);
    // DrawTexture(*skin[currentSkin], 500, 500, WHITE);

    animation.elapsedTime += GetFrameTime();
    if (animation.elapsedTime >= 1.0f / animation.frameRate) {
        animation.currentFrame++;
        animation.elapsedTime = 0.0f;
        if (animation.currentFrame > animation.numFrames - 1) {
            animation.currentFrame = 0;
        }
    }

    DrawTextureRec(
        animation.spriteSheet,
        animation.frameRectangles[animation.currentFrame],
        { 640, 400 },
        WHITE
    );

    DrawTexture(*nextButton, 1090, 500, WHITE);
    DrawTexture(*prevButton, 300, 500, WHITE);

    DrawTexture(*closeButton, 1113, 202, WHITE);

    EndDrawing();
}