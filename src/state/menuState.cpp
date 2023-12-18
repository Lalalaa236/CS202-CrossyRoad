#include "menuState.h"
#include "TextureHolder.h"
#include "gamestate.h"
#include "highscoreState.h"
#include "instructionState.h"
#include "raylib.h"
#include "settingState.h"
#include "skinState.h"
#include <iostream>
#include <utility>
#include"GameSettings.h"

MenuState::MenuState(StateStack &stack) : State(stack) {
    background = &TextureHolder::getHolder().get(Textures::BACKGROUND_MENU);
    button[0] = &TextureHolder::getHolder().get(Textures::BUTTON_0);
    button[1] = &TextureHolder::getHolder().get(Textures::BUTTON_1);
    button[2] = &TextureHolder::getHolder().get(Textures::BUTTON_2);
    button[3] = &TextureHolder::getHolder().get(Textures::BUTTON_3);
    button[4] = &TextureHolder::getHolder().get(Textures::BUTTON_4);
    name = &TextureHolder::getHolder().get(Textures::NAME_LOGO);
    customFont = LoadFont("font/River Adventurer.ttf");
}

// void MenuState::init() {
// }

void MenuState::handleEvents() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        // Get mouse position
        Vector2 mousePosition = GetMousePosition();

        Vector2 a[6] = {{33, 24}, {1352, 28}, {63, 802}, {1352, 804}, {660, 647}, {244, 191}};

        for (int i = 0; i < 5; i++) {
            if (CheckCollisionPointRec(mousePosition,
                                       {a[i].x, a[i].y, button[i]->width * 0.3f, button[i]->height * 0.3f})) {
                switch (i) {

                    /// Intruction button (top left)
                case 0:
                    // nextState = new InstructionState();
                    // nextState->init();
                    requestStackPop();
                    requestStackPush(States::ID::Instructions);
                    break;

                    /// Setting button (top right)
                case 1:
                    // nextState = new settingState(game);
                    // nextState->init();
                    requestStackPop();
                    requestStackPush(States::ID::Settings);
                    break;

                case 2:
                    // nextState = new SkinState();
                    // nextState->init();
                    requestStackPop();
                    requestStackPush(States::ID::Load);
                    break;

                    /// High score button (bottom right)
                case 3:
                    // nextState = new highScoreState();
                    // nextState->init();
                    requestStackPop();
                    requestStackPush(States::ID::Highscore);
                    break;

                    /// Play button (middle)
                case 4:
                    // nextState = new GameState();
                    // nextState->init();
                    requestStackPop();
                    requestStackPush(States::ID::Skin);
                    break;
                }
            }
        }

        if (CheckCollisionPointRec(mousePosition, {a[5].x, a[5].y, name->width * 1.0f, name->height * 1.0f})) {
        }
    }
}

void MenuState::update() {
    // Update logic for the menu state
}

void MenuState::draw() {
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
    Vector2 a[5] = {{33, 24}, {1352, 28}, {63, 802}, {1352, 804}, {660, 647}};
    for (int i = 0; i < 5; i++)
        DrawTextureEx(*button[i],
                      a[i],   // Position
                      0,      // Rotation angle
                      0.3,    // Scale
                      WHITE); // Tint color
    DrawTexture(*name, 244, 191, WHITE);
    const char *text = "Nhat Vy    Nhan Kiet    Hoang Tuan    Cao Tin";
    int fontSize = 40;
    int textWidth = MeasureTextEx(customFont, text, fontSize, 2).x;
    // Calculate the position to center the text horizontally
    Vector2 position = {(float)(settings::SCREEN_WIDTH - textWidth) / 2, 27};
    // Set the custom font and draw text
    DrawTextEx(customFont, text, position, fontSize, 2, BLACK);

}

MenuState::~MenuState() {
    // if (nextState != nullptr) {
    //     delete nextState;
    // }
    // nextState = nullptr;
    requestStackClear();
}
