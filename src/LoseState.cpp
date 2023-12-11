#include "LoseState.h"

LoseState::LoseState(StateStack &stack) : State(stack) {
    board = &TextureHolder::getHolder().get(Textures::ID::LOSE_BOARD);
    restartButton = &TextureHolder::getHolder().get(Textures::ID::RESTART_BUTTON);
    quitButton = &TextureHolder::getHolder().get(Textures::ID::QUIT_BUTTON);
    ShowCursor();
}

LoseState::~LoseState() {
}

void LoseState::draw() {
    ClearBackground(WHITE);
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), SEMI_TRANSPARENT);
    DrawTexture(*board, 289, 107, WHITE);
    DrawTexture(*restartButton, 494.81f, 623.0f, WHITE);
    DrawTexture(*quitButton, 878, 623, WHITE);
}

void LoseState::update() {
}

void LoseState::handleEvents() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePosition = GetMousePosition();
        if (CheckCollisionPointRec(mousePosition,
                                   {494.81, 623.0f, restartButton->width * 1.0f, restartButton->height * 1.0f})) {
            requestStackClear();
            requestStackPush(States::ID::Game);
        } else if (CheckCollisionPointRec(mousePosition,
                                          {878, 623, quitButton->width * 1.0f, quitButton->height * 1.0f})) {
            requestStackClear();
            requestStackPush(States::ID::Menu);
        }
    }
}
