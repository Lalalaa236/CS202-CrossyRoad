#include "PauseState.h"

PauseState::PauseState(StateStack& stack)
: State(stack)
{
    shouldPopState = false;
    board = &TextureHolder::getHolder().get(Textures::ID::PAUSE_BOARD);
    resumeButton = &TextureHolder::getHolder().get(Textures::ID::RESUME_BUTTON);
    ShowCursor();
    // SetConfigFlags(FLAG_WINDOW_TRANSPARENT);
}

PauseState::~PauseState() 
{
    HideCursor();
}

void PauseState::draw()
{
    ClearBackground(WHITE);
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), SEMI_TRANSPARENT);
    DrawTexture(*board, 289, 107, WHITE);
    DrawTexture(*resumeButton, 650, 451, WHITE);
}

void PauseState::update() {}

void PauseState::handleEvents()
{
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Vector2 mousePosition = GetMousePosition();
        if(CheckCollisionPointRec(mousePosition, {650, 451, resumeButton->width * 1.0f, resumeButton->height * 1.0f}))
        {
            requestStackPop();
            // shouldPopState = true;
        }
    }
    else if(IsKeyPressed(KEY_B))
    {
        requestStackPop();
        // shouldPopState = true;
    }
}

// void PauseState::init() {}

bool PauseState::shouldPop() const
{
    return shouldPopState;
}