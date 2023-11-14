#pragma once

class State {
public:
    virtual ~State() = default;
    virtual void handleEvents() = 0;
    virtual void update() = 0;
    virtual void draw() const = 0; 
    virtual bool shouldPop() const = 0;
    State* getNextState() const;
    void setState();
protected:
    bool shouldPopState = false;
    State* nextState = nullptr;
};