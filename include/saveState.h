#ifndef SAVESTATE_H
#define SAVESTATE_H

#include "raylib.h"
#include "save.h"
#include "State.h"
#include "TextureHolder.h"

class SaveState : public State {
private:
    Texture2D* board;
    Texture2D* saveButton;
    Texture2D* quitButton;
    Texture2D* save[3];

    saveData saveDat[3];

    int selectedSlot;

    void handleInput();
    void drawSaveData();
    void drawSaveSlot();

public:
    SaveState(StateStack& stack);
    ~SaveState();

    void draw() override;
    void update() override;
    void handleEvents() override;
};

#endif // SAVESTATE_H