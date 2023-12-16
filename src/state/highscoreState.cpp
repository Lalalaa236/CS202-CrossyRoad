#include "highScoreState.h"
#include "TextureHolder.h"
#include "score.h"
highScoreState::highScoreState(StateStack &stack) : State(stack) {
    background = &TextureHolder::getHolder().get(Textures::BACKGROUND_MENU);
    highScoreBoard = &TextureHolder::getHolder().get(Textures::TABLE_HIGHSCORE);
    closeButton = &TextureHolder::getHolder().get(Textures::CLOSE_BUTTON);
    leaderBoard = &TextureHolder::getHolder().get(Textures::LEADER_BOARD);
    for (int i = 1; i <= 3; i++) {
        score[i - 1] = HighScore::getHighScoreManager().getHighestScore(i);
    }
    customFont = LoadFont("font/JambuKristal-1G01M.otf");
}


void highScoreState::handleEvents() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePosition = GetMousePosition();
        if (CheckCollisionPointRec(mousePosition, {1000, 143, closeButton->width * 1.0f, closeButton->height * 1.0f})) {
            // shouldPopState = true;
            requestStackPop();
            requestStackPush(States::ID::Menu);
        }
    }
}

void highScoreState::update() {
}

void highScoreState::draw() {
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
    DrawTexture(*highScoreBoard, 413, 91, WHITE);
    DrawTexture(*closeButton, 1000, 143, WHITE);
    DrawTexture(*leaderBoard, 530, 300, WHITE);
    for (int i = 0; i < 3; i++) {
        const char *Score = std::to_string(score[i]).c_str();
        DrawTextEx(customFont,
                   Score,
                   Vector2{844, float(370 + i * 160)}, // Centered position
                   40,
                   2,
                   BLACK);
    }
}

highScoreState::~highScoreState() {
}