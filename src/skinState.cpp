#include "skinState.h"
#include <iostream>

void SkinState::setAnimation(int skinIndex, int skinID) {
    animation[skinIndex].setAnimation(mTextureMap[skinID].get(), 4, 4.0f);
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

    numberOfSkins = 0;
    currentSkin = 1;
    animation.push_back(Animation()); // Dummy animation

    // Load skin and set animation
    std::string skinFolderPath = "image/skin/";
    for (int index = 1; ; index++, numberOfSkins++) {
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
    for (auto& pair : this->mTextureMap)
        UnloadTexture(*pair.second);
    this->mTextureMap.clear();

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
        if (CheckCollisionPointRec(mousePosition, { 1090, 500, nextButton->width * 1.0f, nextButton->height * 1.0f })) {
            currentSkin++;
            if (currentSkin > numberOfSkins)
                currentSkin = 1;
        }
        if (CheckCollisionPointRec(mousePosition, { 300, 500, prevButton->width * 1.0f, prevButton->height * 1.0f })) {
            currentSkin--;
            if (currentSkin <= 0)
                currentSkin = numberOfSkins;
        }
    }

    // Close button
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePosition = GetMousePosition();
        if (CheckCollisionPointRec(mousePosition, { 1113, 202, closeButton->width * 1.0f, closeButton->height * 1.0f })) {
            shouldPopState = true;
        }
    }

    // Set button
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePosition = GetMousePosition();
        if (CheckCollisionPointRec(mousePosition, { 680, 700, setButton->width * 1.0f, setButton->height * 1.0f })) {
            // Set the skin to player


            // Pop the state
            // shouldPopState = true;
            requestStackPop();
            requestStackPush(States::ID::Menu);
        }
        if (CheckCollisionPointRec(mousePosition, { 1113, 202, closeButton->width * 1.0f, closeButton->height * 1.0f })) {
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
    int skinBoardX = (GetScreenWidth() - skinBoard->width) / 2;
    int skinBoardY = (GetScreenHeight() - skinBoard->height) / 2;

    ClearBackground(RAYWHITE);
    DrawTexturePro(*background,
        { 0, 0, float(background->width), float(background->height) },
        { 0, 0, background->width * scaleWidth, background->height * scaleHeight },
        { 0, 0 },
        0,
        WHITE);

    DrawTexture(*skinBoard, (GetScreenWidth() - skinBoard->width) / 2, (GetScreenHeight() - skinBoard->height) / 2, WHITE);

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
    Rectangle destRec = {
        (GetScreenWidth() - sourceRec.width * 4.0f) / 2 + 38,
        (GetScreenHeight() - sourceRec.height * 4.0f) / 2 + skinBoard->height / 8,
        sourceRec.width * 4.0f,
        sourceRec.height * 4.0f
    };
    Vector2 origin = { sourceRec.width * 0.5f, sourceRec.height * 0.5f };
    DrawTexturePro(animation[currentSkin].spriteSheet, sourceRec, destRec, origin, 0.0f, WHITE);

    // Calculate the coordinates relative to the skinBoard
    float closeButtonX = skinBoardX + skinBoard->width - closeButton->width;
    float closeButtonY = skinBoardY + skinBoard->height / 5.5f;
    float nextButtonX = skinBoardX + skinBoard->width - nextButton->width;
    float nextButtonY = skinBoardY + (skinBoard->height - nextButton->height) / 2 + skinBoard->height / 10;
    float prevButtonX = skinBoardX;
    float prevButtonY = skinBoardY + (skinBoard->height - prevButton->height) / 2 + skinBoard->height / 10;
    float setButtonX = skinBoardX + (skinBoard->width - setButton->width) / 2;
    float setButtonY = skinBoardY + skinBoard->height - setButton->height;

    // Draw the buttons
    DrawTexture(*closeButton, closeButtonX, closeButtonY, WHITE);
    DrawTexture(*nextButton, nextButtonX, nextButtonY, WHITE);
    DrawTexture(*prevButton, prevButtonX, prevButtonY, WHITE);
    DrawTexture(*setButton, setButtonX, setButtonY, WHITE);
}