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