#include "State.h"
#include "StateStack.h"

State::State(StateStack& stack) : stack(&stack) {
}

void State::requestStackPush(States::ID stateID) {
    stack->pushState(stateID);
}

void State::requestStackPop() {
    stack->popState();
}

void State::requestStackClear() {
    stack->clearState();
}

State* State::getState(States::ID stateID) {
    return stack->getState(stateID);
}