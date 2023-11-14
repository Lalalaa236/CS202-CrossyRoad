#pragma once

#include"raylib.h"
#include <stack>


class State;

class Game {
public:
    Game();
    ~Game();

    void run();
private:

    std::stack<State*> stateStack;
};
