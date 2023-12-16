#include "saveState.h"
#include "save.h"
#include <iostream>

saveData save[3];

void SaveState::drawSaveSlot(int selectedSlot) {
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
        DrawText(("Slot " + std::to_string(i + 1)).c_str(),
                 saveSlotX + 50 * scaleWidth,
                 saveSlotY + i * 150 * scaleHeight + 10 * scaleHeight,
                 40 * scaleHeight,
                 WHITE);

        // Draw the save slot data
        if (save[i].getSerializedData() != "") {
            DrawText(("Score: " + std::to_string(save[i].getHighScore())).c_str(),
                     saveSlotX + 50 * scaleWidth,
                     saveSlotY + i * 150 * scaleHeight + 60 * scaleHeight,
                     40 * scaleHeight,
                     WHITE);
        } else {
            DrawText("Empty",
                     saveSlotX + 50 * scaleWidth,
                     saveSlotY + i * 150 * scaleHeight + 60 * scaleHeight,
                     40 * scaleHeight,
                     WHITE);
        }
    }
}

SaveState::SaveState(StateStack &stack) : State(stack) {
    confirmSave = false;

    // Load texture from outside
    quitButton = &TextureHolder::getHolder().get(Textures::CLOSE_BUTTON);
    saveButton = new Texture2D(LoadTexture("image/saveState/saveButton.png"));
    board = new Texture2D(LoadTexture("image/saveState/board.png"));
    confirmSavePanel = new Texture2D(LoadTexture("image/saveState/confirmSavePanel.png"));
    saveSlot = new Texture2D(LoadTexture("image/saveState/saveSlot.png"));
    saveSlotSelected = new Texture2D(LoadTexture("image/saveState/selectedSlot.png"));
    greySaveButton = new Texture2D(LoadTexture("image/saveState/greySaveButton.png"));
    cancelButton = new Texture2D(LoadTexture("image/saveState/cancelButton.png"));

    // Calculate the coordinates relative to the board
    scaleWidth = (float)GetScreenWidth() / settings::SCREEN_WIDTH;
    scaleHeight = (float)GetScreenHeight() / settings::SCREEN_HEIGHT;

    boardX = (GetScreenWidth() - board->width * scaleWidth) / 2;
    boardY = (GetScreenHeight() - board->height * scaleHeight) / 2;
    confirmSavePanelX = (GetScreenWidth() - confirmSavePanel->width * scaleWidth) / 2;
    confirmSavePanelY = (GetScreenHeight() - confirmSavePanel->height * scaleHeight) / 2;
    saveButtonX = boardX + (board->width - saveButton->width * scaleWidth) / 2;
    saveButtonY = boardY + board->height * scaleHeight - saveButton->height * scaleHeight + 10 * scaleHeight;
    quitButtonX = boardX + board->width - quitButton->width;
    quitButtonY = boardY + board->height / 5.5f;

    saveSlotX = boardX + (board->width - saveSlot->width * scaleWidth) / 2;
    saveSlotY = boardY + (board->width * 0.29f);

    // Load save data
    for (int i = 0; i < 3; ++i)
        save[i].load(i);
}

SaveState::~SaveState() {
    UnloadTexture(*board);
    UnloadTexture(*confirmSavePanel);
    UnloadTexture(*saveSlot);
    UnloadTexture(*saveButton);
    UnloadTexture(*saveSlotSelected);
    UnloadTexture(*greySaveButton);
    UnloadTexture(*cancelButton);

    delete board;
    delete confirmSavePanel;
    delete saveSlot;
    delete saveButton;
    delete saveSlotSelected;
    delete greySaveButton;
    delete cancelButton;
}

void SaveState::drawNormalSave() {
    // Draw the board
    DrawTexturePro(*board,
                   {0, 0, float(board->width), float(board->height)},
                   {float(boardX), float(boardY), board->width * scaleWidth, board->height * scaleHeight},
                   {0, 0},
                   0,
                   WHITE);

    // Draw the save button
    if (selectedSlot == -1) {
        DrawTexturePro(*greySaveButton,
                       {0, 0, float(greySaveButton->width), float(greySaveButton->height)},
                       {float(saveButtonX),
                        float(saveButtonY),
                        greySaveButton->width * scaleWidth,
                        greySaveButton->height * scaleHeight},
                       {0, 0},
                       0,
                       WHITE);
    } else {
        DrawTexturePro(
            *saveButton,
            {0, 0, float(saveButton->width), float(saveButton->height)},
            {float(saveButtonX), float(saveButtonY), saveButton->width * scaleWidth, saveButton->height * scaleHeight},
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

    // Draw 3 save slots
    drawSaveSlot(this->selectedSlot);
}

void SaveState::drawConfirmSave() {
    // Draw the confirm save panel
    DrawTexturePro(*confirmSavePanel,
                   {0, 0, float(confirmSavePanel->width), float(confirmSavePanel->height)},
                   {float(confirmSavePanelX),
                    float(confirmSavePanelY),
                    confirmSavePanel->width * scaleWidth,
                    confirmSavePanel->height * scaleHeight},
                   {0, 0},
                   0,
                   WHITE);

    // Draw the save button (Right side)
    DrawTexturePro(*saveButton,
                   {0, 0, float(saveButton->width), float(saveButton->height)},
                   {float(confirmSavePanelX + confirmSavePanel->width * scaleWidth - saveButton->width * scaleWidth -
                          100 * scaleWidth),
                    float(confirmSavePanelY + confirmSavePanel->height * scaleHeight -
                          saveButton->height * scaleHeight - 20 * scaleHeight),
                    saveButton->width * scaleWidth,
                    saveButton->height * scaleHeight},
                   {0, 0},
                   0,
                   WHITE);

    // Draw the cancel button (Left side)
    DrawTexturePro(*cancelButton,
                   {0, 0, float(cancelButton->width), float(cancelButton->height)},
                   {float(confirmSavePanelX + 100 * scaleWidth),
                    float(confirmSavePanelY + confirmSavePanel->height * scaleHeight -
                          cancelButton->height * scaleHeight - 20 * scaleHeight),
                    cancelButton->width * scaleWidth,
                    cancelButton->height * scaleHeight},
                   {0, 0},
                   0,
                   WHITE);
}

void SaveState::draw() {
    ClearBackground(WHITE);
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), SEMI_TRANSPARENT);

    if (confirmSave == false) {
        drawNormalSave();
        return;
    }

    drawConfirmSave();
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
    // On the normal save panel
    if (confirmSave == false && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePos = GetMousePosition();

        // Check if the mouse is clicked on the save button and the selected slot is not empty
        if (mousePos.x >= saveButtonX && mousePos.x <= saveButtonX + saveButton->width * scaleWidth &&
            mousePos.y >= saveButtonY && mousePos.y <= saveButtonY + saveButton->height * scaleHeight) {
            if (save[selectedSlot].getSerializedData() != "") {
                confirmSave = true;
                return;
            }

            if (selectedSlot == -1)
                return;

            // Save the data
            State *gameState = getState(2); // States::ID::Game
            std::string serializedData = dynamic_cast<GameState *>(gameState)->serializeData();

            save[selectedSlot].setSerializedData(serializedData);
            save[selectedSlot].save(selectedSlot);

            // Pop the save state and push the pause state
            requestStackPop();
            requestStackPush(States::ID::Pause);
        }

        this->selectedSlot = -1;

        // Check if the mouse is clicked on the quit button
        if (mousePos.x >= quitButtonX && mousePos.x <= quitButtonX + quitButton->width * scaleWidth &&
            mousePos.y >= quitButtonY && mousePos.y <= quitButtonY + quitButton->height * scaleHeight) {
            requestStackPop();
            requestStackPush(States::ID::Pause);
        }

        for (int i = 0; i < 3; ++i) {
            if (mousePos.x >= saveSlotX && mousePos.x <= saveSlotX + saveSlot->width * scaleWidth &&
                mousePos.y >= saveSlotY + i * 150 * scaleHeight &&
                mousePos.y <= saveSlotY + i * 150 * scaleHeight + saveSlot->height * scaleHeight) {
                this->selectedSlot = i;
            }
        }
    }

    // On the confirm save panel
    if (confirmSave == true && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePos = GetMousePosition();

        if (mousePos.x >= confirmSavePanelX + confirmSavePanel->width * scaleWidth - saveButton->width * scaleWidth -
                              100 * scaleWidth &&
            mousePos.x <= confirmSavePanelX + confirmSavePanel->width * scaleWidth - 100 * scaleWidth &&
            mousePos.y >= confirmSavePanelY + confirmSavePanel->height * scaleHeight -
                              saveButton->height * scaleHeight - 20 * scaleHeight &&
            mousePos.y <= confirmSavePanelY + confirmSavePanel->height * scaleHeight - 20 * scaleHeight) {
            // Save the data
            State *gameState = getState(2);
            std::string serializedData = dynamic_cast<GameState *>(gameState)->serializeData();

            save[selectedSlot].setSerializedData(serializedData);
            save[selectedSlot].save(selectedSlot);

            // Pop the save state and push the pause state
            requestStackPop();
            requestStackPush(States::ID::Pause);
        }

        // Cancel the save
        if (mousePos.x >= confirmSavePanelX + 100 * scaleWidth &&
            mousePos.x <= confirmSavePanelX + 100 * scaleWidth + cancelButton->width * scaleWidth &&
            mousePos.y >= confirmSavePanelY + confirmSavePanel->height * scaleHeight -
                              cancelButton->height * scaleHeight - 20 * scaleHeight &&
            mousePos.y <= confirmSavePanelY + confirmSavePanel->height * scaleHeight - 20 * scaleHeight) {
            confirmSave = false;
        }
    }
}