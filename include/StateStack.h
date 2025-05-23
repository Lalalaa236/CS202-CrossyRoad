#ifndef STATESTACK_H
#define STATESTACK_H

#include "State.h"
#include "StateIdentifiers.h"
#include <functional>
#include <map>
#include <vector>

class StateStack {
public:
    enum class Action { Push, Pop, Clear };
    StateStack();
    ~StateStack();

    bool isEmpty() const;

    template <typename T>
    void registerState(States::ID id);

    void pushState(States::ID id);
    void popState();
    void clearState();

    State* getState(int index = 1);

    void update();
    void draw();
    void handleEvents();

private:
    struct PendingChange {
        explicit PendingChange(Action action, States::ID stateID = States::ID::None);
        Action action;
        States::ID state;
    };

    std::vector<State::Ptr> states;
    std::vector<PendingChange> pendingList;
    std::map<States::ID, std::function<State::Ptr()>> factories;

    State::Ptr createState(States::ID id);

    void applyPendingChanges();
};

template <typename T>
void StateStack::registerState(States::ID id) {
    factories[id] = [this]() { return State::Ptr(new T(*this)); };
}

#endif