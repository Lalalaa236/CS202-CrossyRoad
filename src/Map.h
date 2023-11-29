#ifndef MAP_H
#define MAP_H

#include "lane.h"

class Map
{
    private:
        std::deque<Lane*> lanes;
        float speed;
    public:
        Map(float speed);
        void draw();
        void update();
        void setSpeed(float speed);
        bool CheckCollisionPLayer(Rectangle playerBoxCollision);
        ~Map();
};

#endif