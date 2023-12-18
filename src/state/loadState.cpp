#include "loadState.h"
#include <iostream>

saveData saveDatas[3];

LoadState::LoadState(StateStack &stack) : State(stack) {
    // Load texture from outside
    background = &TextureHolder::getHolder().get(Textures::BACKGROUND_MENU);
    quitButton = &TextureHolder::getHolder().get(Textures::CLOSE_BUTTON);
    loadButton = new Texture2D(LoadTexture("image/loadState/loadButton.png"));
    greyLoadButton = new Texture2D(LoadTexture("image/loadState/greyLoadButton.png"));
    board = new Texture2D(LoadTexture("image/loadState/board.png"));
    saveSlot = new Texture2D(LoadTexture("image/saveState/saveSlot.png"));
    saveSlotSelected = new Texture2D(LoadTexture("image/saveState/selectedSlot.png"));
    customFont = LoadFont("font/JambuKristal-1G01M.otf");

    // Calculate scale
    scaleWidth = (float)GetScreenWidth() / settings::SCREEN_WIDTH;
    scaleHeight = (float)GetScreenHeight() / settings::SCREEN_HEIGHT;

    // Calculate position
    boardX = (GetScreenWidth() - board->width * scaleWidth) / 2;
    boardY = (GetScreenHeight() - board->height * scaleHeight) / 2;
    loadButtonX = boardX + (board->width - loadButton->width * scaleWidth) / 2;
    loadButtonY = boardY + board->height * scaleHeight - loadButton->height * scaleHeight + 10 * scaleHeight;
    quitButtonX = boardX + board->width - quitButton->width;
    quitButtonY = boardY + board->height / 5.5f;

    saveSlotX = boardX + (board->width - saveSlot->width * scaleWidth) / 2;
    saveSlotY = boardY + (board->width * 0.29f);

    // Load save data
    for (int i = 0; i < 3; ++i) {
        saveDatas[i].load(i);
    }
}

LoadState::~LoadState() {
    UnloadTexture(*board);
    UnloadTexture(*loadButton);
    UnloadTexture(*greyLoadButton);
    UnloadTexture(*saveSlot);
    UnloadTexture(*saveSlotSelected);

    delete board;
    delete loadButton;
    delete greyLoadButton;
    delete saveSlot;
    delete saveSlotSelected;
}

void LoadState::drawSaveSlot(int selectedSlot) {
    for (int i = 0; i < 3; ++i) {
        // Draw the save slot
        if (i == selectedSlot) {
            DrawTexturePro(*saveSlotSelected,
                           {0, 0, float(saveSlotSelected->width), float(saveSlotSelected->height)},
                           {float(saveSlotX),
                            float(saveSlotY + i * 150 * scaleHeight),
                            saveSlotSelected->width * scaleWidth,
                            saveSlotSelected->height * scaleHeight},
                           {0, 0},
                           0,
                           WHITE);
        } else {
            DrawTexturePro(*saveSlot,
                           {0, 0, float(saveSlot->width), float(saveSlot->height)},
                           {float(saveSlotX),
                            float(saveSlotY + i * 150 * scaleHeight),
                            saveSlot->width * scaleWidth,
                            saveSlot->height * scaleHeight},
                           {0, 0},
                           0,
                           WHITE);
        }

        // Draw the save slot number
        DrawTextEx(customFont,("Slot " + std::to_string(i + 1)).c_str(),
                Vector2{saveSlotX + 50 * scaleWidth,
                saveSlotY + i * 150 * scaleHeight + 10 * scaleHeight},
                40 * scaleHeight,
                2,
                WHITE);

        // Draw the save slot data
        if (saveDatas[i].getSerializedData() != "") {
            DrawTextEx(customFont,("Score: " + std::to_string(saveDatas[i].getHighScore())).c_str(),
                    Vector2{saveSlotX + 50 * scaleWidth,
                    saveSlotY + i * 150 * scaleHeight + 60 * scaleHeight},
                    40 * scaleHeight,
                    2,
                    WHITE);
        } else {
            DrawTextEx(customFont,"Empty",
                    Vector2{saveSlotX + 50 * scaleWidth,
                    saveSlotY + i * 150 * scaleHeight + 60 * scaleHeight},
                    40 * scaleHeight,
                    2,
                    WHITE);
        }
    }
}

void LoadState::drawBoard() {
    ClearBackground(RAYWHITE);

    // Draw background
    DrawTexturePro(*background,
                   {0, 0, float(background->width), float(background->height)},
                   {0, 0, background->width * scaleWidth, background->height * scaleHeight},
                   {0, 0},
                   0,
                   WHITE);

    // Draw the board
    DrawTexturePro(*board,
                   {0, 0, float(board->width), float(board->height)},
                   {float(boardX), float(boardY), board->width * scaleWidth, board->height * scaleHeight},
                   {0, 0},
                   0,
                   WHITE);

    // Draw the load button
    if (selectedSlot != -1) {
        DrawTexturePro(
            *loadButton,
            {0, 0, float(loadButton->width), float(loadButton->height)},
            {float(loadButtonX), float(loadButtonY), loadButton->width * scaleWidth, loadButton->height * scaleHeight},
            {0, 0},
            0,
            WHITE);
    } else {
        DrawTexturePro(*greyLoadButton,
                       {0, 0, float(greyLoadButton->width), float(greyLoadButton->height)},
                       {float(loadButtonX),
                        float(loadButtonY),
                        greyLoadButton->width * scaleWidth,
                        greyLoadButton->height * scaleHeight},
                       {0, 0},
                       0,
                       WHITE);
    }

    // Draw the quit button
    DrawTexturePro(
        *quitButton,
        {0, 0, float(quitButton->width), float(quitButton->height)},
        {float(quitButtonX), float(quitButtonY), quitButton->width * scaleWidth, quitButton->height * scaleHeight},
        {0, 0},
        0,
        WHITE);

    // Draw the save slot
    drawSaveSlot(this->selectedSlot);
}

void LoadState::handleInput() {
    if (IsKeyPressed(KEY_ESCAPE)) {
        requestStackPop();
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePos = GetMousePosition();

        // Check if the mouse is on the load button
        if (mousePos.x >= loadButtonX && mousePos.x <= loadButtonX + loadButton->width * scaleWidth &&
            mousePos.y >= loadButtonY && mousePos.y <= loadButtonY + loadButton->height * scaleHeight) {
            if (selectedSlot != -1) {
                // Set the data
                data::Game = saveDatas[selectedSlot].getGameData();
                data::Map = saveDatas[selectedSlot].getMapData();
                data::Player = saveDatas[selectedSlot].getPlayerData();

                // Push the game state
                requestStackPop();
                requestStackPush(States::ID::Game);
            }
        }

        // Check if the mouse is on the quit button
        if (mousePos.x >= quitButtonX && mousePos.x <= quitButtonX + quitButton->width * scaleWidth &&
            mousePos.y >= quitButtonY && mousePos.y <= quitButtonY + quitButton->height * scaleHeight) {
            requestStackPop();
            requestStackPush(States::ID::Menu);
        }

        // Check if the mouse is on the save slot
        selectedSlot = -1;
        for (int i = 0; i < 3; ++i) {
            if (saveDatas[i].getSerializedData() == "")
                continue;

            if (mousePos.x >= saveSlotX && mousePos.x <= saveSlotX + saveSlot->width * scaleWidth &&
                mousePos.y >= saveSlotY + i * 150 * scaleHeight &&
                mousePos.y <= saveSlotY + i * 150 * scaleHeight + saveSlot->height * scaleHeight) {
                this->selectedSlot = i;
            }
        }
    }
}

void LoadState::draw() {
    drawBoard();
}

void LoadState::update() {
}

void LoadState::handleEvents() {
    handleInput();
}
