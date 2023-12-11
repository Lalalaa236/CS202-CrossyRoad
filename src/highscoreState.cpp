#include "highScoreState.h"
#include "TextureHolder.h"
highScoreState::highScoreState(StateStack& stack) 
: State(stack)
{
    background = &TextureHolder::getHolder().get(Textures::BACKGROUND_MENU);
    highScoreBoard = &TextureHolder::getHolder().get(Textures::TABLE_HIGHSCORE);
    closeButton = &TextureHolder::getHolder().get(Textures::CLOSE_BUTTON);
}

// void highScoreState::init() {
//     // background = LoadTexture("../CS202-CROSSROAD/image/highscore/bg.png");
//     // highScoreBoard =
//     // LoadTexture("../CS202-CROSSROAD/image/highscore/highScoreBoard.png");
//     // closeButton =
//     // LoadTexture("../CS202-CROSSROAD/image/highscore/closeButton.png");
// }

void highScoreState::handleEvents() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePosition = GetMousePosition();
        if (CheckCollisionPointRec(mousePosition, {1113, 202, closeButton->width * 1.0f, closeButton->height * 1.0f})) {
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
    DrawTexture(*highScoreBoard, 319, 81, WHITE);
    DrawTexture(*closeButton, 1113, 202, WHITE);
}

highScoreState::~highScoreState() {
}