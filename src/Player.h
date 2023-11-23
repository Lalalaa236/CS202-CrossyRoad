#ifndef PLAYER_H
#define PLAYER_H

#include "GameSettings.h"

class Player
{
    private:
        std::pair<float, float> position;
        bool isAlive;
        void up();
        void down();
        void left();
        void right();
    public:
        enum class Direction
        {
            UP,
            DOWN,
            LEFT,
            RIGHT
        };
        Player(float x, float y);
        Player(float x, float y, bool isAlive);
        std::pair<float, float> getPosition();
        void move(Direction direction);
        bool getIsAlive();
};

#endif