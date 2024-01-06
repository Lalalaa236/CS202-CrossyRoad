#include "PauseState.h"
#include "score.h"
PauseState::PauseState(StateStack& stack) : State(stack), timerCount(0.0f) {
    board = &TextureHolder::getHolder().get(Textures::ID::PAUSE_BOARD);
    resumeButton = &TextureHolder::getHolder().get(Textures::ID::RESUME_BUTTON);
    restartButton = &TextureHolder::getHolder().get(Textures::ID::RESTART_BUTTON);
    quitButton = &TextureHolder::getHolder().get(Textures::ID::QUIT_BUTTON);
    saveButton = &TextureHolder::getHolder().get(Textures::ID::SAVE_BUTTON);
    timer = &TextureHolder::getHolder().get(Textures::ID::TIMER_3);

    ShowCursor();
}

PauseState::~PauseState() {
}

void PauseState::draw() {
    ClearBackground(WHITE);
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), SEMI_TRANSPARENT);

    if (timerCount == 0.0f) {
        DrawTexture(*board, 289, 107, WHITE);
        DrawTexture(*resumeButton, 644, 417, WHITE);
        DrawTexture(*restartButton, 479.9f, 593.89f, WHITE);
        DrawTexture(*quitButton, 658, 588, WHITE);
        DrawTexture(*saveButton, 847, 593, WHITE);
    }
    else {
        DrawTexture(*timer, 638, 408, WHITE);
    }
}

void PauseState::update() {
    if (timerCount != 0.0f) {
        HideCursor();
        if (GetTime() - timerCount < 3.0f)
            timer = &TextureHolder::getHolder().get(
                (Textures::ID)(Textures::ID::TIMER_3 - (Textures::ID)(GetTime() - timerCount)));
        else
            requestStackPop();
    }
}

void PauseState::handleEvents() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && timerCount == 0.0f) {
        Vector2 mousePosition = GetMousePosition();
        if (CheckCollisionPointRec(mousePosition, { 644, 417, resumeButton->width * 1.0f, resumeButton->height * 1.0f }))
            timerCount = GetTime();
        // shouldPopState = true;
        else if (CheckCollisionPointRec(mousePosition,
            { 479.9f, 593.89f, restartButton->width * 1.0f, restartButton->height * 1.0f })) {
            requestStackClear();
            requestStackPush(States::ID::Game);
            HighScore::getHighScoreManager().setCurrentScore(0);
        }
        else if (CheckCollisionPointRec(mousePosition,
            { 658, 588, quitButton->width * 1.0f, quitButton->height * 1.0f })) {
            requestStackClear();
            requestStackPush(States::ID::Menu);
        }
        else if (CheckCollisionPointRec(mousePosition,
            { 847, 593, saveButton->width * 1.0f, saveButton->height * 1.0f })) {
            requestStackPop();
            requestStackPush(States::ID::Save);
        }
    }
    else if (IsKeyPressed(KEY_B)) {
        requestStackPop();
        // shouldPopState = true;
    }
}