#ifndef MAP_H
#define MAP_H

#include "lane.h"

class Map {
private:
    std::deque<Lane*> lanes;
    float speed;
    Sound hitVehicle;
    Sound hitAnimal;

public:
    Map(float speed);
    ~Map();

    void draw();
    void update(int score = 0);

    void setSpeed(float speed);
    float getSpeed() const;
    bool CheckCollisionPlayer(Rectangle playerBoxCollision);

    std::string serializeData();
    void loadSerializedData(const std::string& serialized_data);
};

#endif
    