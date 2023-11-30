#include"settingState.h"
#include"TextureHolder.h"
#include<iostream>

settingState::settingState(Game& game) : game(game) {
    shouldPopState = false;
}

void settingState::init() {
    background = &TextureHolder::getHolder().get(Textures::BACKGROUND_MENU);
    settingBoard = &TextureHolder::getHolder().get(Textures::TABLE_SETTING);
    sound[0] = &TextureHolder::getHolder().get(Textures::SOUND_ON);
    sound[1] = &TextureHolder::getHolder().get(Textures::SOUND_OFF);
    sound[2] = &TextureHolder::getHolder().get(Textures::GREY_BAR);
    sound[3] = &TextureHolder::getHolder().get(Textures::GREEN_BAR);
    sound[4] = &TextureHolder::getHolder().get(Textures::DOT);
    closeButton = &TextureHolder::getHolder().get(Textures::CLOSE_BUTTON);
    float initialVolume = game.getVolume();
    dotPosition.x = 613 + initialVolume * (sound[2]->width - 27);
    dotPosition.y = 491;
}

void settingState::handleEvents() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePosition = GetMousePosition();
        if (CheckCollisionPointRec(mousePosition, { 1113,202,closeButton->width * 1.0f,closeButton->height * 1.0f })) {
            shouldPopState = true;
        }

        if (CheckCollisionPointRec(mousePosition, { 445,449,sound[0]->width * 1.0f,sound[1]->height * 1.0f })) {
            game.toggleSound();
        }

        /*
                if (CheckCollisionPointRec(mousePosition, { 613,500,sound[2]->width * 1.0f,sound[2]->height * 1.0f })) {
                    if (!game.getSoundState()) {
                        game.toggleSound();
                    }

                    float newVolume = (mousePosition.x - 613) / sound[2]->width;
                    if (newVolume > 1.0f) newVolume = 1.0f;
                    if (newVolume < 0.0f) newVolume = 0.0f;

                    game.setVolume(newVolume);
                    setDot(newVolume);
                }
        */
    }

    static bool isDragging = false;
    static Vector2 dragOffset;

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePosition = GetMousePosition();

        // Check if the mouse is pressed on the slider
        if (CheckCollisionPointRec(mousePosition, { 613, 500, sound[2]->width * 1.0f, sound[2]->height * 1.0f })) {
            isDragging = true;
            dragOffset.x = mousePosition.x - dotPosition.x;
            dragOffset.y = mousePosition.y - dotPosition.y;
        }
    }

    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        isDragging = false;

    if (isDragging) {
        // Turn on the sound if it was off
        if (!game.getSoundState()) {
            game.toggleSound();
        }

        Vector2 mousePosition = GetMousePosition();

        // Calculate the new position of the dot based on the mouse position and the drag offset
        dotPosition.x = mousePosition.x - dragOffset.x;

        // Ensure the dot stays within the bounds of the slider
        if (dotPosition.x < 615) {
            dotPosition.x = 615;
        }
        else if (dotPosition.x > 613 + sound[2]->width - 27) {
            dotPosition.x = 613 + sound[2]->width - 27;
        }

        // Calculate the new volume based on the position of the dot
        float newVolume = (dotPosition.x - 613) / (sound[2]->width);

        if (newVolume > 1.0f) newVolume = 1.0f;
        if (newVolume < 0.0f) newVolume = 0.0f;

        // Set the new volume value in your application
        game.setVolume(newVolume);
    }
}

void settingState::update() {

}

void settingState::setDot(float volume) {
    float initialVolume = game.getVolume();
    dotPosition.x = 613 + initialVolume * (sound[2]->width - 27);
    dotPosition.y = 491;
}

void settingState::draw() {
    float scaleWidth = (float)GetScreenWidth() / background->width;
    float scaleHeight = (float)GetScreenHeight() / background->height;
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // Draw background image
    DrawTexturePro(
        *background,
        { 0, 0, float(background->width), float(background->height) },
        { 0, 0, background->width * scaleWidth, background->height * scaleHeight },
        { 0, 0 },
        0,
        WHITE
    );

    DrawTexture(*settingBoard, 319, 81, WHITE);
    DrawTexture(*closeButton, 1113, 202, WHITE);
    if (game.getSoundState()) {
        DrawTexture(*sound[0], 445, 449, WHITE);
        if (game.getVolume() == 0.0f) {
            game.setVolume(1.0f);
            setDot(1.0f);
        }
    }
    else {
        DrawTexture(*sound[1], 445, 449, WHITE);
        game.setVolume(0.0f);
        setDot(0.0f);
    }

    DrawTexture(*sound[2], 613, 500, WHITE);
    Rectangle sourceRec = { 0, 0, static_cast<float>(dotPosition.x - 613), static_cast<float>(sound[3]->height) };
    Rectangle destRec = { 613, 500, static_cast<float>(dotPosition.x - 613), static_cast<float>(sound[3]->height) };
    DrawTexturePro(*sound[3], sourceRec, destRec, { 0, 0 }, 0, WHITE);
    DrawTexture(*sound[4], dotPosition.x, dotPosition.y, WHITE);
    EndDrawing();
}

settingState::~settingState() {

}

bool settingState::shouldPop() const {
    return shouldPopState;
}