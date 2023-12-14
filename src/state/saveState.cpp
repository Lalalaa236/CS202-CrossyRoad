#include "saveState.h"
#include "save.h"
#include <iostream>

float scaleWidth = 1.0f;
float scaleHeight = 1.0f;
int boardX = 0, boardY = 0;
int confirmSavePanelX = 0, confirmSavePanelY = 0;
int saveButtonX = 0, saveButtonY = 0;
int quitButtonX = 0, quitButtonY = 0;
int saveSlotX = 0, saveSlotY = 0;

saveData save[3];

void SaveState::drawSaveSlot() {
    for (int i = 0; i < 3; ++i) {
        // Draw the save slot
        DrawTexturePro(*saveSlot,
            { 0, 0, float(saveSlot->width), float(saveSlot->height) },
            { float(saveSlotX), float(saveSlotY + i * 150 * scaleHeight), saveSlot->width * scaleWidth, saveSlot->height * scaleHeight },
            { 0, 0 },
            0,
            WHITE);

        // Draw the save slot number
        DrawText(std::to_string(i + 1).c_str(),
            saveSlotX + 50 * scaleWidth,
            saveSlotY + i * 150 * scaleHeight + 10 * scaleHeight,
            40 * scaleHeight,
            WHITE);

        // Draw the save slot data
        if (save[i].getSerializedData() != "") {
            DrawText(std::to_string(save[i].getHighScore()).c_str(),
                saveSlotX + 50 * scaleWidth,
                saveSlotY + i * 150 * scaleHeight + 100 * scaleHeight,
                50 * scaleHeight,
                WHITE);
            DrawText(std::to_string(save[i].getHighScore()).c_str(),
                saveSlotX + 50 * scaleWidth,
                saveSlotY + i * 150 * scaleHeight + 150 * scaleHeight,
                50 * scaleHeight,
                WHITE);
        }
        else
        {
            DrawText("Empty",
                saveSlotX + 50 * scaleWidth,
                saveSlotY + i * 150 * scaleHeight + 60 * scaleHeight,
                40 * scaleHeight,
                WHITE);
        }
    }
}

SaveState::SaveState(StateStack& stack) : State(stack) {
    quitButton = &TextureHolder::getHolder().get(Textures::CLOSE_BUTTON);

    // Load texture from outside
    saveButton = new Texture2D(LoadTexture("image/saveState/saveButton.png"));
    board = new Texture2D(LoadTexture("image/saveState/board.png"));
    confirmSavePanel = new Texture2D(LoadTexture("image/saveState/confirmSavePanel.png"));
    saveSlot = new Texture2D(LoadTexture("image/saveState/saveSlot.png"));

    // Calculate the coordinates relative to the board
    scaleWidth = (float)GetScreenWidth() / settings::SCREEN_WIDTH;
    scaleHeight = (float)GetScreenHeight() / settings::SCREEN_HEIGHT;

    boardX = (GetScreenWidth() - board->width * scaleWidth) / 2;
    boardY = (GetScreenHeight() - board->height * scaleHeight) / 2;
    confirmSavePanelX = boardX + (board->width - confirmSavePanel->width * scaleWidth) / 2;
    confirmSavePanelY = boardY + (board->height - confirmSavePanel->height * scaleHeight) / 2;
    saveButtonX = boardX + (board->width - saveButton->width * scaleWidth) / 2;
    saveButtonY = boardY + board->height * scaleHeight - saveButton->height * scaleHeight + 10 * scaleHeight;
    quitButtonX = boardX + board->width - quitButton->width;
    quitButtonY = boardY + board->height / 5.5f;

    saveSlotX = boardX + (board->width - saveSlot->width * scaleWidth) / 2;
    saveSlotY = boardY + (board->width * 0.29f);

    // Load save data
    // TODO
}

SaveState::~SaveState() {
    UnloadTexture(*board);
    UnloadTexture(*confirmSavePanel);
    UnloadTexture(*saveSlot);
    UnloadTexture(*saveButton);

    delete board;
    delete confirmSavePanel;
    delete saveSlot;
    delete saveButton;
}

void SaveState::draw() {
    ClearBackground(WHITE);
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), SEMI_TRANSPARENT);

    // Draw the board
    DrawTexturePro(*board,
        { 0, 0, float(board->width), float(board->height) },
        { float(boardX), float(boardY), board->width * scaleWidth, board->height * scaleHeight },
        { 0, 0 },
        0,
        WHITE);

    // Draw the save button
    DrawTexturePro(*saveButton,
        { 0, 0, float(saveButton->width), float(saveButton->height) },
        { float(saveButtonX), float(saveButtonY), saveButton->width * scaleWidth, saveButton->height * scaleHeight },
        { 0, 0 },
        0,
        WHITE);

    // Draw the quit button
    DrawTexturePro(*quitButton,
        { 0, 0, float(quitButton->width), float(quitButton->height) },
        { float(quitButtonX), float(quitButtonY), quitButton->width * scaleWidth, quitButton->height * scaleHeight },
        { 0, 0 },
        0,
        WHITE);

    // Draw 3 save slots
    drawSaveSlot();
}

void SaveState::update() {
    // static int i = 0;
    // if(i++ == 0)
    //     std::cout << "SaveState update called" << std::endl;
}

void SaveState::handleEvents() {
    handleInput();
}

void SaveState::handleInput() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePos = GetMousePosition();

        // Check if the mouse is clicked on the save button
        if (mousePos.x >= saveButtonX && mousePos.x <= saveButtonX + saveButton->width * scaleWidth &&
            mousePos.y >= saveButtonY && mousePos.y <= saveButtonY + saveButton->height * scaleHeight) {
            // Save the data
            // save[selectedSlot].save(selectedSlot);
            requestStackPop();
        }

        // Check if the mouse is clicked on the quit button
        if (mousePos.x >= quitButtonX && mousePos.x <= quitButtonX + quitButton->width * scaleWidth &&
            mousePos.y >= quitButtonY && mousePos.y <= quitButtonY + quitButton->height * scaleHeight) {
            requestStackPop();
        }
    }
}