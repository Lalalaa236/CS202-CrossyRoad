#ifndef SAVESTATE_H
#define SAVESTATE_H

#include "raylib.h"
#include "gameState.h"
#include "save.h"
#include "State.h"
#include "TextureHolder.h"

class SaveState : public State {
private:
    Texture2D* board;                   // Background board
    Texture2D* confirmSavePanel;        // Panel to confirm overwrite save data 
    Texture2D* saveButton;              // Button to save data
    Texture2D* greySaveButton;          // Button to save data (grey)
    Texture2D* cancelButton;            // Button to cancel save data
    Texture2D* quitButton;              // Button to quit save state
    Texture2D* saveSlot;                // Save slots
    Texture2D* saveSlotSelected;        // Save slots selected

    float scaleWidth = 1.0f;
    float scaleHeight = 1.0f;
    int boardX = 0, boardY = 0;
    int confirmSavePanelX = 0, confirmSavePanelY = 0;
    int saveButtonX = 0, saveButtonY = 0;
    int quitButtonX = 0, quitButtonY = 0;
    int saveSlotX = 0, saveSlotY = 0;

    void handleInput();
    void drawSaveSlot(int selectedSlot = -1);
    void drawNormalSave();
    void drawConfirmSave();

    int selectedSlot = -1;              // Selected save slot
    bool confirmSave = false;           // Confirm save panel
public:
    SaveState(StateStack& stack);
    ~SaveState();

    void draw() override;
    void update() override;
    void handleEvents() override;
};

#endif // SAVESTATE_H