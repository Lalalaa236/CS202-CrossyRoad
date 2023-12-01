#pragma once
#include "raylib.h"

class State {
public:
    virtual ~State() = default;
    virtual void handleEvents() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual bool shouldPop() const = 0;
    State *getNextState() const;
    void setState();
    virtual void init() = 0;

protected:
    bool shouldPopState = false;
    State *nextState = nullptr;
};