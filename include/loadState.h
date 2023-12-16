#ifndef LOADSTATE_H
#define LOADSTATE_H

#include "raylib.h"
#include "gameState.h"
#include "save.h"
#include "State.h"
#include "TextureHolder.h"

class LoadState : public State {
private:
    Texture2D* board;                   // Background board
    Texture2D* loadButton;              // Button to load data
    Texture2D* greyLoadButton;          // Button to load data (grey)
    Texture2D* quitButton;              // Button to quit load state
    Texture2D* saveSlot;                // Save slots
    Texture2D* saveSlotSelected;        // Save slots selected

    void handleInput();
    void drawSaveSlot(int selectedSlot = -1);
    void drawLoad();

    int selectedSlot = -1;              // Selected load slot
public:
    LoadState(StateStack& stack);
    ~LoadState();

    void draw() override;
    void update() override;
    void handleEvents() override;
};

#endif // LOADSTATE_H