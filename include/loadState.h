#ifndef LOADSTATE_H
#define LOADSTATE_H

#include "raylib.h"
#include "gameState.h"
#include "save.h"
#include "State.h"
#include "TextureHolder.h"

class LoadState : public State {
private:
    Texture2D* background;              // Background
    Texture2D* board;                   // Background board
    Texture2D* loadButton;              // Button to load data
    Texture2D* greyLoadButton;          // Button to load data (grey)
    Texture2D* quitButton;              // Button to quit load state
    Texture2D* saveSlot;                // Save slots
    Texture2D* saveSlotSelected;        // Save slots selected

    float scaleWidth = 1.0f;
    float scaleHeight = 1.0f;
    int boardX = 0, boardY = 0;
    int loadButtonX = 0, loadButtonY = 0;
    int quitButtonX = 0, quitButtonY = 0;
    int saveSlotX = 0, saveSlotY = 0;

    void handleInput();
    void drawSaveSlot(int selectedSlot = -1);
    void drawBoard();

    int selectedSlot = -1;              // Selected load slot
public:
    LoadState(StateStack& stack);
    ~LoadState();

    void draw() override;
    void update() override;
    void handleEvents() override;
};

#endif // LOADSTATE_H