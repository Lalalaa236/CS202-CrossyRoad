#ifndef STATESTACK_H
#define STATESTACK_H

#include <vector>
#include <map>
#include <functional>
#include "State.h"
#include "StateIdentifiers.h"

class StateStack 
{
    public:
        enum class Action
        {
            Push,
            Pop,
            Clear
        };
        StateStack();
        ~StateStack();

        bool isEmpty() const;

        template <typename T>
        void registerState(States::ID id);
        
        void pushState(States::ID id);
        void popState();
        void clearState();

        void update();
        void draw();
        void handleEvents();

        void applyPendingChanges();

    private:
        struct PendingChange
        {
            explicit PendingChange(Action action, States::ID stateID = States::ID::None);
            Action action;
            States::ID state;
        };
        std::vector<State::Ptr> states;
        std::vector<PendingChange> pendingList;
        std::map<States::ID, std::function<State::Ptr()>> factories;
        
        State::Ptr createState(States::ID id);

};

template <typename T>
void StateStack::registerState(States::ID id)
{
    factories[id] = [this] ()
    {
        return State::Ptr(new T(*this));
    };
}

#endif