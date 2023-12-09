#include "StateStack.h"
#include <iostream>
#include <cassert>

StateStack::StateStack()
{
    std::cout << "StateStack created" << std::endl;
}

State::Ptr StateStack::createState(States::ID id)
{
    auto found = factories.find(id);
    assert(found != factories.end());
    // std::cout << "Creating state " << (int)id << std::endl;
    return found->second();
}

void StateStack::handleEvents()
{
    states.back()->handleEvents();

    applyPendingChanges();
}

void StateStack::update()
{
    states.back()->update();

    applyPendingChanges();
}

void StateStack::draw()
{
    BeginDrawing();
    for(auto& state : states)
        state->draw();
    EndDrawing();
}

void StateStack::applyPendingChanges()
{
    for(auto &change : pendingList)
    {
        switch(change.action)
        {
            case Action::Push:
                std::cout << "Pushing state " << (int)change.state << std::endl;
                states.push_back(createState(change.state));
                std::cout << "Pushed state " << (int)change.state << std::endl;
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

StateStack::~StateStack()
{
    clearState();
}

void StateStack::pushState(States::ID id)
{
    pendingList.push_back(PendingChange{Action::Push, id});
}

void StateStack::popState()
{
    pendingList.push_back(PendingChange{Action::Pop});
}

void StateStack::clearState()
{
    pendingList.push_back(PendingChange{Action::Clear});
}

bool StateStack::isEmpty() const
{
    return states.empty();
}

StateStack::PendingChange::PendingChange(Action action, States::ID stateID)
: action(action), state(stateID)
{}