#pragma once

#include "raylib.h"
#include "settingState.h"
#include <stack>

class State;

class Game {
public:
    Game();
    ~Game();

    void loadAllTexture();
    void run();

    void toggleSound();
    float getVolume();
    void setVolume(float volume);
    bool getSoundState();
    void setSoundState(bool ok);

private:
    Music bgMusic;
    float volume;
    bool soundEnabled;

    std::stack<State *> stateStack;
};
