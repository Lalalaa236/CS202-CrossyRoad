#pragma once

#include "State.h"
#include "TextureHolder.h"
#include "player.h"
#include "raylib.h"

#include <iostream>
#include <map>
#include <vector>

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

    Animation& operator=(const Animation& other) {
        if (this != &other) {
            delete[] frameRectangles;

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
        return *this;
    }

    void setAnimation(Texture2D* skin, int numFrames, float frameRate) {
        Texture2D* skinSpriteSheet = skin;

        int frameWidth = skinSpriteSheet->width / 4;
        int frameHeight = skinSpriteSheet->height / 8;

        // std::cerr << frameWidth << " " << frameHeight << std::endl;

        Rectangle* frames = new Rectangle[numFrames];

        for (int i = 0; i < numFrames; i++) {
            frames[i].x = frameWidth * i;
            frames[i].y = 0;
            frames[i].width = frameWidth;
            frames[i].height = frameHeight;
        }

        spriteSheet = *skinSpriteSheet;
        frameRectangles = frames;
        this->numFrames = numFrames;
        this->frameRate = frameRate;
        currentFrame = 0;
        elapsedTime = 0.0f;
    }
};

/// @brief Use to change the skin of the player
class SkinState : public State {
private:
    int numberOfSkins;
    std::map<int, std::unique_ptr<Texture2D>> mTextureMap;
    std::vector<Animation> animation;

    Texture2D* background;
    Texture2D* skinBoard;
    Texture2D* closeButton;
    Texture2D* nextButton;
    Texture2D* prevButton;
    Texture2D* setButton;

    int currentSkin = 0;

    void setAnimation(int skinIndex, int skinID);

public:
    SkinState(StateStack& stack);
    ~SkinState();

    // void init() override;
    bool shouldPop() const override;

    void handleEvents() override;
    void update() override;
    void draw() override;
};