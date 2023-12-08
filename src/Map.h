#ifndef MAP_H
#define MAP_H

#include "lane.h"
#include<vector>
#include"Obstacle.h"
class Map {
private:
    std::deque<Lane*> lanes;
    float speed;

public:
    Map(float speed);
    void draw();
    void update();
    void setSpeed(float speed);
    bool CheckCollisionPlayer(Rectangle playerBoxCollision);
    ~Map();
    void updatePause();
    void save(std::vector<std::pair<Obstacle*,float>>& v);
    void rePlay(std::vector<std::pair<Obstacle*,float>>& v);
};

#endif