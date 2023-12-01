#include "State.h"

State *State::getNextState() const {
    return nextState;
}

void State::setState() {
    nextState = nullptr;
}