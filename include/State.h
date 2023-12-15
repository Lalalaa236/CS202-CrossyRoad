#pragma once
#include "StateIdentifiers.h"
#include "raylib.h"
#include <memory>

class StateStack;

class State {
public:
    typedef std::unique_ptr<State> Ptr;
    State(StateStack& stack);
    virtual ~State() {
    }
    virtual void handleEvents() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    // virtual void init() = 0;

protected:
    void requestStackPush(States::ID stateID);
    void requestStackPop();
    void requestStackClear();

    State* getState(States::ID stateID);

private:
    StateStack* stack = nullptr;
};