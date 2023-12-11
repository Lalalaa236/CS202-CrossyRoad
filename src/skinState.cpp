#include "skinState.h"
#include "TextureHolder.h"
#include "settingState.h"

#include <iostream>

void SkinState::setAnimation(int skinIndex, int skinID) {
    animation[skinIndex].setAnimation(mTextureMap[skinID].get(), 4, 4.0f);
}

SkinState::SkinState(StateStack &stack) : State(stack) {
    skinBoard = &TextureHolder::getHolder().get(Textures::SKIN_TABLE);
    background = &TextureHolder::getHolder().get(Textures::BACKGROUND_MENU);
    closeButton = &TextureHolder::getHolder().get(Textures::CLOSE_BUTTON);
    nextButton = &TextureHolder::getHolder().get(Textures::NEXT_BUTTON);
    prevButton = &TextureHolder::getHolder().get(Textures::PREVIOUS_BUTTON);
    setButton = &TextureHolder::getHolder().get(Textures::CONFIRM_BUTTON);

    numberOfSkins = 0;
    currentSkin = settings::CURRENT_SKIN;
    animation.push_back(Animation()); // Dummy animation

    // Load skin and set animation
    std::string skinFolderPath = "image/skin/";
    for (int index = 1;; index++, numberOfSkins++) {
        std::string skinPath = skinFolderPath + '/' + std::to_string(index) + '/';

        // Check if any sprite sheet is missing
        if (!FileExists((skinPath + "/full.png").c_str())) {
            numberOfSkins = index - 1;
            break;
        }

        // Load sprite sheet
        std::unique_ptr<Texture2D> fullSheet(new Texture2D());
        *fullSheet = LoadTexture((skinPath + "/full.png").c_str());
        mTextureMap[index] = std::move(fullSheet);

        // Set animation
        animation.push_back(Animation());
        setAnimation(index, index);
    }
}

SkinState::~SkinState() {

    // Unload all texture
    for (auto &pair : this->mTextureMap)
        UnloadTexture(*pair.second);
    this->mTextureMap.clear();
}

// Variable
int skinBoardX = 0, skinBoardY = 0;

// Calculate the coordinates relative to the skinBoard
float closeButtonX = 0, closeButtonY = 0;
float nextButtonX = 0, nextButtonY = 0;
float prevButtonX = 0, prevButtonY = 0;
float setButtonX = 0, setButtonY = 0;

// Function

void SkinState::handleEvents() {
    // Next and previous button
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePosition = GetMousePosition();
        if (CheckCollisionPointRec(mousePosition,
                                   {nextButtonX, nextButtonY, nextButton->width * 1.0f, nextButton->height * 1.0f})) {
            currentSkin++;
            if (currentSkin > numberOfSkins)
                currentSkin = 1;
        }
        if (CheckCollisionPointRec(mousePosition,
                                   {prevButtonX, prevButtonY, prevButton->width * 1.0f, prevButton->height * 1.0f})) {
            currentSkin--;
            if (currentSkin <= 0)
                currentSkin = numberOfSkins;
        }
    }

    // Close button
    // if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    //     Vector2 mousePosition = GetMousePosition();
    //     if (CheckCollisionPointRec(mousePosition, { 1113, 202, closeButton->width * 1.0f, closeButton->height * 1.0f })) {
    //        requestStackPop();
    //     }
    // }

    // Set button
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePosition = GetMousePosition();
        if (CheckCollisionPointRec(mousePosition,
                                   {setButtonX, setButtonY, setButton->width * 1.0f, setButton->height * 1.0f})) {

            // Copy the current skin into SKIN_FULL ID
            TextureHolder::getHolder().load(Textures::SKIN_FULL,
                                            "image/skin/" + std::to_string(currentSkin) + "/full.png");
            settings::CURRENT_SKIN = currentSkin;

            // Pop the state
            requestStackPop();
            requestStackPush(States::ID::Game);
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
    skinBoardX = (GetScreenWidth() - skinBoard->width) / 2;
    skinBoardY = (GetScreenHeight() - skinBoard->height) / 2;

    // Calculate the coordinates relative to the skinBoard
    closeButtonX = skinBoardX + skinBoard->width - closeButton->width;
    closeButtonY = skinBoardY + skinBoard->height / 5.5f;
    nextButtonX = skinBoardX + skinBoard->width - nextButton->width;
    nextButtonY = skinBoardY + (skinBoard->height - nextButton->height) / 2 + skinBoard->height / 10;
    prevButtonX = skinBoardX;
    prevButtonY = skinBoardY + (skinBoard->height - prevButton->height) / 2 + skinBoard->height / 10;
    setButtonX = skinBoardX + (skinBoard->width - setButton->width) / 2;
    setButtonY = skinBoardY + skinBoard->height - setButton->height;

    ClearBackground(RAYWHITE);
    DrawTexturePro(*background,
                   {0, 0, float(background->width), float(background->height)},
                   {0, 0, background->width * scaleWidth, background->height * scaleHeight},
                   {0, 0},
                   0,
                   WHITE);

    DrawTexture(*skinBoard,
                (GetScreenWidth() - skinBoard->width) / 2,
                (GetScreenHeight() - skinBoard->height) / 2,
                WHITE);

    // Draw the animation of skin
    animation[currentSkin].elapsedTime += GetFrameTime();
    if (animation[currentSkin].elapsedTime >= 1.0f / animation[currentSkin].frameRate) {
        animation[currentSkin].currentFrame++;
        animation[currentSkin].elapsedTime = 0.0f;
        if (animation[currentSkin].currentFrame > animation[currentSkin].numFrames - 1) {
            animation[currentSkin].currentFrame = 0;
        }
    }

    Rectangle sourceRec = animation[currentSkin].frameRectangles[animation[currentSkin].currentFrame];
    Rectangle destRec = {(GetScreenWidth() - sourceRec.width * 4.0f) / 2 + 38,
                         (GetScreenHeight() - sourceRec.height * 4.0f) / 2 + skinBoard->height / 8,
                         sourceRec.width * 4.0f,
                         sourceRec.height * 4.0f};
    Vector2 origin = {sourceRec.width * 0.5f, sourceRec.height * 0.5f};
    DrawTexturePro(animation[currentSkin].spriteSheet, sourceRec, destRec, origin, 0.0f, WHITE);

    // Draw the buttons
    DrawTexture(*closeButton, closeButtonX, closeButtonY, WHITE);
    DrawTexture(*nextButton, nextButtonX, nextButtonY, WHITE);
    DrawTexture(*prevButton, prevButtonX, prevButtonY, WHITE);
    DrawTexture(*setButton, setButtonX, setButtonY, WHITE);
}