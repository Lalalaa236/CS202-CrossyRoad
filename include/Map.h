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

    void draw();
    void update(int score = 0);

    void setSpeed(float speed);
    bool CheckCollisionPlayer(Rectangle playerBoxCollision);

    std::string serializeData();
    void loadSerializedData(std::string serialized_data);
};

#endif