#include "LoseState.h"
#include "gameState.h"
#include "StateStack.h"
#include"score.h"
LoseState::LoseState(StateStack& stack)
: State(stack){
    board = &TextureHolder::getHolder().get(Textures::ID::LOSE_BOARD);
    restartButton = &TextureHolder::getHolder().get(Textures::ID::RESTART_BUTTON);
    quitButton = &TextureHolder::getHolder().get(Textures::ID::QUIT_BUTTON);
    customFont = LoadFont("font/JambuKristal-1G01M.otf");

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
    DrawTexture(*restartButton, 494.81f, 623.0f, WHITE);
    DrawTexture(*quitButton, 878, 623, WHITE);
    const char* scoreText = "Score";
    const char* actualScore = std::to_string(HighScore::getHighScoreManager().getCurrentScore()).c_str();

    // Measure the width of the "Score:" text
    float scoreTextWidth = MeasureTextEx(customFont, scoreText, 100, 2).x;

    // Draw "Score:"
    DrawTextEx(customFont, scoreText,
            Vector2{730 - scoreTextWidth / 2, 426}, // Centered position
            100,
            2,
            RED);

    // Draw the actual score centered with respect to "Score:"
    DrawTextEx(customFont, actualScore,
            Vector2{730 - MeasureTextEx(customFont, actualScore, 100, 2).x / 2, 540}, // Centered position
            100,
            2,
            RED);

}

void LoseState::update() {
}

void LoseState::handleEvents()
{
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        Vector2 mousePosition = GetMousePosition();
        if(CheckCollisionPointRec(mousePosition, {494.81, 623.0f, restartButton->width * 1.0f, restartButton->height * 1.0f})){
            requestStackClear();
            requestStackPush(States::ID::Game);
            HighScore::getHighScoreManager().setCurrentScore(0);
        }    
        else if(CheckCollisionPointRec(mousePosition, {878, 623, quitButton->width * 1.0f, quitButton->height * 1.0f}))
        {
            requestStackClear();
            requestStackPush(States::ID::Menu);
        }
    }
}
   