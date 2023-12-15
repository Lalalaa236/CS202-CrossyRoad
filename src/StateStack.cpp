#include "StateStack.h"
#include <cassert>
#include <iostream>

StateStack::StateStack() {
}

State::Ptr StateStack::createState(States::ID id) {

    auto found = factories.find(id);
    assert(found != factories.end());
    //std::cout << "Creating state " << (int)id << std::endl;
    return found->second();
}

void StateStack::handleEvents() {
    if (states.size() > 0)
        states.back()->handleEvents();

    applyPendingChanges();
}

void StateStack::update() {
    if (states.size() > 0)
        states.back()->update();

    applyPendingChanges();
}

void StateStack::draw() {
    if (states.size() > 0) {
        BeginDrawing();
        for (auto& state : states)
            state->draw();
        EndDrawing();
    }
}

void StateStack::applyPendingChanges() {
    for (auto& change : pendingList) {
        switch (change.action) {
        case Action::Push:
            states.push_back(createState(change.state));
            break;
        case Action::Pop:
            states.pop_back();
            break;
        case Action::Clear:
            states.clear();
            break;
        default:
            break;
        }
    }

    pendingList.clear();
}

StateStack::~StateStack() {
    clearState();
    applyPendingChanges();
}

void StateStack::pushState(States::ID id) {
    pendingList.push_back(PendingChange{ Action::Push, id });
}

void StateStack::popState() {
    pendingList.push_back(PendingChange{ Action::Pop });
}

void StateStack::clearState() {
    pendingList.push_back(PendingChange{ Action::Clear });
}

State* StateStack::getState(States::ID id) {
    return states[states.size() - 2].get();
}

bool StateStack::isEmpty() const {
    return states.empty();
}

StateStack::PendingChange::PendingChange(Action action, States::ID stateID) : action(action), state(stateID) {
}