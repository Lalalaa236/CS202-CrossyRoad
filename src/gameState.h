#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "Player.h"
#include "Map.h"

class GameState : public State
{
    private:
        Player* player;
        Map* map;
    public:
        GameState();
        ~GameState();
        void draw() override;
        void update() override;
        bool shouldPop() const override;
        void init() override;
        void handleEvents() override;
};

#endif