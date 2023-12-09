#include "StateStack.h"

template <typename T>
void StateStack::registerState(States::ID id)
{
    factories[id] = [this] ()
    {
        return State::Ptr(new T(*this));
    };
}

State::Ptr StateStack::createState(States::ID id)
{
    auto found = factories.find(id);
    if (found == factories.end())
    {
        return nullptr;
    }
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
    for(auto& state : states)
    {
        state->draw();
    }
}

void StateStack::applyPendingChanges()
{
    for(PendingChange &change : pendingList)
    {
        switch(change.action)
        {
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