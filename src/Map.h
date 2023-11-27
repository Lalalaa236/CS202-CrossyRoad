#ifndef MAP_H
#define MAP_H

#include "lane.h"

class Map {
private:
    std::deque<Lane*> lanes;
    float speed;

public:
    Map(float speed);
    ~Map();

    void setSpeed(float speed);

    void draw();
    void update();
};

#endif