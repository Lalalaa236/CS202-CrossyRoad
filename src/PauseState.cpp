#include "PauseState.h"

PauseState::PauseState() 
{
    board = &TextureHolder::getHolder().get(Textures::ID::PAUSE_BOARD);
    resumeButton = &TextureHolder::getHolder().get(Textures::ID::RESUME_BUTTON);
}

PauseState::~PauseState() {}

void PauseState::draw()
{
    BeginDrawing();
    DrawTexture(*board, 305, 79, WHITE);
    DrawTexture(*resumeButton, 350, 85, WHITE);
    EndDrawing();
}

void PauseState::update() {}

void PauseState::handleEvents()
{
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Vector2 mousePosition = GetMousePosition();
        if(CheckCollisionPointRec(mousePosition, {350, 85, resumeButton->width * 1.0f, resumeButton->height * 1.0f}))
        {
            shouldPopState = true;
        }
    }
}

void PauseState::init() {}

bool PauseState::shouldPop() const
{
    return shouldPopState;
}