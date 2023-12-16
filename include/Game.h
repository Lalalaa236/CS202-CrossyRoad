#pragma once

#include "MusicManager.h"
#include "StateStack.h"
#include "raylib.h"

#include "gameState.h"
#include "highscoreState.h"
#include "instructionState.h"
#include "LoseState.h"
#include "menuState.h"
#include "pauseState.h"
#include "settingState.h"
#include "skinState.h"
#include "saveState.h"
#include "loadState.h"


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
