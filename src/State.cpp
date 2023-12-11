#include "State.h"
#include "StateStack.h"

State::State(StateStack& stack) 
: stack(&stack) {}

State *State::getNextState() const {
    return nextState;
}

void State::setState() {
    nextState = nullptr;
}

void State::requestStackPush(States::ID stateID) 
{
    stack->pushState(stateID);
}

void State::requestStackPop() 
{
    stack->popState();
}

void State::requestStackClear() 
{
    stack->clearState();
}