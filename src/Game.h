#pragma once

#include"raylib.h"
#include <stack>
#include"settingState.h"

class State;

class Game {
public:
    Game();
    ~Game();
    void loadAllTexture();
    void run();
    void toggleSound();
    bool getSoundState();
    float getVolume();
    void setVolume(float volume);
    void setSoundState(bool ok);
private:
    Music bgMusic;
    float volume;
    bool soundEnabled;
    std::stack<State*> stateStack;
};
