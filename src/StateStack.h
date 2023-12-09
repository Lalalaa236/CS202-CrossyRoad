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
        StateStack() = default;
        ~StateStack();

        template <typename T>
        void registerState(States::ID id);
        
        void pushState(States::ID id);
        void popState();
        void clearState();

        void update();
        void draw();
        void handleEvents();

    private:
        struct PendingChange
        {
            Action action;
            States::ID state;
        };
        std::vector<State::Ptr> states;
        std::vector<PendingChange> pendingList;
        std::map<States::ID, std::function<State::Ptr()>> factories;
        
        State::Ptr createState(States::ID id);

        void applyPendingChanges();
};

#endif