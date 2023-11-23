#ifndef MAP_H
#define MAP_H

#include "lane.h"

class Map
{
    private:
        std::deque<Lane*> lanes;
        float speed;
    public:
        Map();
        void draw();
        void update();
        void setSpeed(float speed);
        ~Map();
};

#endif