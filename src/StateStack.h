#ifndef STATESTACK_H
#define STATESTACK_H

#include "State.h"
#include <vector>
#include <map>
#include <functional>

enum class StateID
{
    Title,
    Menu,
    Game,
    Pause,
    Instruction,
    GameOver
};

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

        template <typename T>
        void registerState(StateID id);
        
        void push(State* state);
        void pop();
        void clear();

        void update();
        void draw();
        
    private:
        struct PendingChange
        {
            Action action;
            State* state;
        };
        std::vector<State*> states;
        std::vector<PendingChange> pendingList;
        std::map<StateID, std::function<State*()>> factories;
        
        State* createState(StateID id);
        void applyPendingChanges();
};

#endif