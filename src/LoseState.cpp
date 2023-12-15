#include "LoseState.h"
#include "gameState.h"
#include "StateStack.h"
#include"score.h"
LoseState::LoseState(StateStack& stack)
: State(stack){
    board = &TextureHolder::getHolder().get(Textures::ID::LOSE_BOARD);
    restartButton = &TextureHolder::getHolder().get(Textures::ID::RESTART_BUTTON);
    quitButton = &TextureHolder::getHolder().get(Textures::ID::QUIT_BUTTON);
    customFont = LoadFontEx("font/River Adventurer.ttf",110, 0, 250);
    //SetTextureFilter(customFont.texture, FILTER_BILINEAR);
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
    float scoreTextWidth = MeasureTextEx(customFont, scoreText, 110, 2).x;

    // Center the "Score:" text within the board
    Vector2 scoreTextPos = {
        289 + (board->width - scoreTextWidth) / 2, // Center horizontally
        426 // Fixed vertical position
    };

    // Draw "Score:"
    Color textColor = Color{0xF3, 0x96, 0x44, 0xFF};
    DrawTextEx(customFont, scoreText,
               scoreTextPos,
               110,
               2,
               textColor);

    // Draw the actual score centered with respect to "Score"
    Vector2 actualScorePos = {
        289 + (board->width - MeasureTextEx(customFont, actualScore, 110, 2).x) / 2, 
        550 // Fixed vertical position
    };

    DrawTextEx(customFont, actualScore,
               actualScorePos,
               90,
               2,
               textColor);
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
   