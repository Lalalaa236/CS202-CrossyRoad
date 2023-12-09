#pragma once
#include "raylib.h"
#include <memory>
#include "StateIdentifiers.h"

class StateStack;

class State {
public:
    typedef std::unique_ptr<State> Ptr;
    State(StateStack& stack);
    virtual ~State() {}
    virtual void handleEvents() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual bool shouldPop() const = 0;
    State *getNextState() const;
    void setState();
    // virtual void init() = 0;

protected:
    bool shouldPopState = false;
    State *nextState = nullptr;

    void requestStackPush(States::ID stateID);
    void requestStackPop();
    void requestStackClear();

private:
    StateStack* stack = nullptr;
};