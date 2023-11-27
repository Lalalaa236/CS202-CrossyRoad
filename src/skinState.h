#pragma once

#include "State.h"
#include "raylib.h"
#include "TextureHolder.h"

struct Animation {
    Texture2D spriteSheet;
    Rectangle* frameRectangles = nullptr;
    int numFrames;
    float frameRate;
    int currentFrame;
    float elapsedTime;

    Animation() {
        spriteSheet = {};
        frameRectangles = nullptr;
        numFrames = 0;
        frameRate = 0.0f;
        currentFrame = 0;
        elapsedTime = 0.0f;
    }

    ~Animation() {
        delete[] frameRectangles;
    }

    Animation(const Animation& other) {
        spriteSheet = other.spriteSheet;
        numFrames = other.numFrames;
        frameRate = other.frameRate;
        currentFrame = other.currentFrame;
        elapsedTime = other.elapsedTime;

        frameRectangles = new Rectangle[numFrames];
        for (int i = 0; i < numFrames; i++) {
            frameRectangles[i] = other.frameRectangles[i];
        }
    }
};

/// @brief Use to change the skin of the player
class SkinState : public State {
private:
    Animation animation;

    Texture2D* background;
    Texture2D* skinBoard;
    Texture2D* closeButton;
    Texture2D* nextButton;
    Texture2D* prevButton;

    Texture2D* skin[5];
    int currentSkin;

    void drawAnimation();
public:
    SkinState();
    ~SkinState();

    void init() override;
    bool shouldPop() const override;

    void handleEvents() override;
    void update() override;
    void draw() override;
};