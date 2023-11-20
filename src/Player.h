#ifndef PLAYER_H
#define PLAYER_H

#include "GameSettings.h"

class Player
{
    private:
        std::pair<float, float> position;
        bool isAlive;
    public:
        Player(float x, float y);
        Player(float x, float y, bool isAlive);
        void up();
        void down();
        void left();
        void right();
        std::pair<float, float> getPosition();
};

#endif