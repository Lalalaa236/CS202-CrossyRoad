#include "settingState.h"
#include "TextureHolder.h"
#include <iostream>

settingState::settingState(StateStack &stack)
: State(stack)
{
    background = &TextureHolder::getHolder().get(Textures::BACKGROUND_MENU);
    settingBoard = &TextureHolder::getHolder().get(Textures::TABLE_SETTING);
    sound[0] = &TextureHolder::getHolder().get(Textures::SOUND_ON);
    sound[1] = &TextureHolder::getHolder().get(Textures::SOUND_OFF);
    sound[2] = &TextureHolder::getHolder().get(Textures::GREY_BAR);
    sound[3] = &TextureHolder::getHolder().get(Textures::GREEN_BAR);
    sound[4] = &TextureHolder::getHolder().get(Textures::DOT);
    closeButton = &TextureHolder::getHolder().get(Textures::CLOSE_BUTTON);
    float initialVolume = MusicManager::getManager().getVolume();
    dotPosition.x = 613 + initialVolume * (sound[2]->width - 27);
    dotPosition.y = 491;
}

// void settingState::init() {
//     // float initialVolume = game.getVolume();
//     // dotPosition.x = 613 + initialVolume * (sound[2]->width - 27);
//     // dotPosition.y = 491;
// }

void settingState::handleEvents() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePosition = GetMousePosition();
        if (CheckCollisionPointRec(mousePosition, { 1113, 202, closeButton->width * 1.0f, closeButton->height * 1.0f })) {
            requestStackPop();
            requestStackPush(States::ID::Menu);
        }

        if (CheckCollisionPointRec(mousePosition, {445, 449, sound[0]->width * 1.0f, sound[1]->height * 1.0f})) {
            MusicManager::getManager().toggleSound();
        }
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
        if (CheckCollisionPointRec(mousePosition, {1113, 202, closeButton->width * 1.0f, closeButton->height * 1.0f})) {
            requestStackPop();
            requestStackPush(States::ID::Menu);
        }
    }

    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        isDragging = false;

    if (isDragging) {
        // Turn on the sound if it was off
        if (!MusicManager::getManager().getIsSoundOn()) {
            MusicManager::getManager().toggleSound();
        }

        Vector2 mousePosition = GetMousePosition();

        // Calculate the new position of the dot based on the mouse position and the
        // drag offset
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

        if (newVolume > 1.0f)
            newVolume = 1.0f;
        if (newVolume < 0.0f)
            newVolume = 0.0f;

        // Set the new volume value in your application
        MusicManager::getManager().setVolume(newVolume);
    }
}

void settingState::update() {
    float initialVolume = MusicManager::getManager().getVolume();
    dotPosition.x = 613 + initialVolume * (sound[2]->width - 27);
    dotPosition.y = 491;
}


void settingState::draw() {
    float scaleWidth = (float)GetScreenWidth() / background->width;
    float scaleHeight = (float)GetScreenHeight() / background->height;
    ClearBackground(RAYWHITE);

    // Draw background image
    DrawTexturePro(*background,
        { 0, 0, float(background->width), float(background->height) },
        { 0, 0, background->width * scaleWidth, background->height * scaleHeight },
        { 0, 0 },
        0,
        WHITE);

    DrawTexture(*settingBoard, 319, 81, WHITE);
    DrawTexture(*closeButton, 1113, 202, WHITE);
    if (MusicManager::getManager().getIsSoundOn()) {
        DrawTexture(*sound[0], 445, 449, WHITE);
        if (MusicManager::getManager().getVolume() == 0.0f) {
            MusicManager::getManager().setVolume(1.0f);
        }
    } else {
        DrawTexture(*sound[1], 445, 449, WHITE);
        MusicManager::getManager().setVolume(0.0f);
    }

    DrawTexture(*sound[2], 613, 500, WHITE);
    Rectangle sourceRec = { 0, 0, static_cast<float>(dotPosition.x - 613), static_cast<float>(sound[3]->height) };
    Rectangle destRec = { 613, 500, static_cast<float>(dotPosition.x - 613), static_cast<float>(sound[3]->height) };
    DrawTexturePro(*sound[3], sourceRec, destRec, { 0, 0 }, 0, WHITE);
    DrawTexture(*sound[4], dotPosition.x, dotPosition.y, WHITE);
}

settingState::~settingState() {
}