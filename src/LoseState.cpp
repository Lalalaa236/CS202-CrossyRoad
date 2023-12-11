#include "LoseState.h"

LoseState::LoseState(StateStack& stack)
: State(stack){
    board = &TextureHolder::getHolder().get(Textures::ID::LOSE_BOARD);
    restartButton = &TextureHolder::getHolder().get(Textures::ID::RESTART_BUTTON);
    quitButton = &TextureHolder::getHolder().get(Textures::ID::QUIT_BUTTON);
    ShowCursor();
}

LoseState::~LoseState() 
{
}

void LoseState::draw()
{
    ClearBackground(WHITE);
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), SEMI_TRANSPARENT);
    DrawTexture(*board, 289, 107, WHITE);
    DrawTexture(*restartButton, 479.9f, 593.89f, WHITE);
    DrawTexture(*quitButton, 658, 588, WHITE);
}

void LoseState::update() 
{
    
}

void LoseState::handleEvents()
{
    // if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && timerCount == 0.0f)
    // {
    //     Vector2 mousePosition = GetMousePosition();
    //     if(CheckCollisionPointRec(mousePosition, {650, 451, resumeButton->width * 1.0f, resumeButton->height * 1.0f}))
    //         timerCount = GetTime();
    //         // shouldPopState = true;
    //     else if(CheckCollisionPointRec(mousePosition, {485, 627, restartButton->width * 1.0f, restartButton->height * 1.0f}))
    //     {
    //         requestStackClear();
    //         requestStackPush(States::ID::Game);
    //     }    
    //     else if(CheckCollisionPointRec(mousePosition, {664, 622, quitButton->width * 1.0f, quitButton->height * 1.0f}))
    //     {
    //         requestStackClear();
    //         requestStackPush(States::ID::Menu);
    //     }
    //     else if(CheckCollisionPointRec(mousePosition, {853, 627, saveButton->width * 1.0f, saveButton->height * 1.0f}))
    //     {
    //     }
    // }
    // else if(IsKeyPressed(KEY_B))
    // {
    //     requestStackPop();
    //     // shouldPopState = true;
    // }
}