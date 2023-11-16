#pragma once

#include"raylib.h"
#include <stack>


class State;

class Game {
public:
    Game();
    ~Game();
    void loadAllTexture();
    void run();
private:
    Music bgMusic;
    std::stack<State*> stateStack;
};
