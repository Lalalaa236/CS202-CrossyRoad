#pragma once

#include "raylib.h"
#include "MusicManager.h"
#include "StateStack.h"

#include "gameState.h"
#include "menuState.h"
#include "pauseState.h"
#include "highscoreState.h"
#include "skinState.h"
#include "instructionState.h"
#include "settingState.h"


class State;

class Game {
public:
    Game();
    ~Game();

    void loadAllTexture();
    void run();

    // void toggleSound();
    // float getVolume();
    // void setVolume(float volume);
    // bool getSoundState();
    // void setSoundState(bool ok);

private:
    Music bgMusic;
    float volume;
    bool soundEnabled;

    StateStack stateStack;

    void registerState();
};
