#ifndef PLAYER_H
#define PLAYER_H

#include "GameSettings.h"
#include "TextureHolder.h"

class Player
{
    private:
        std::pair<float, float> position;
        float mapSpeed;
        bool isAlive;
        void up();
        void down();
        void left();
        void right();
        Rectangle boxCollision;
    public:
        enum class Direction
        {
            UP,
            DOWN,
            LEFT,
            RIGHT
        };
        Player(float x, float y, float mapSpeed);
        Player(float x, float y, bool isAlive);
        
        std::pair<float, float> getPosition();
        bool getIsAlive();
        void setIsAlive(bool isAlive);
        void setMapSpeed(float mapSpeed);
        Rectangle getBoxCollision();

        void move(Direction direction);
        void update();
        void draw();
};

#endif