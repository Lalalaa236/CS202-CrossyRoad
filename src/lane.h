#ifndef LANE_H
#define LANE_H

#include "Obstacle.h"
#include "trafficlight.h"
#include <deque>
#include "TextureHolder.h"

class Lane {
public:
    Lane(float y, float mapSpeed);
    ~Lane();

    void setY(float y);
    float getY() const;
    void setSpeed(float mapSpeed);

    void addObstacle();
    void draw();
    void update();

private:
    float y;
    float mapSpeed;
    float randomSpeed;
    bool isSafe;

    const Texture2D* texture;
    std::deque<Obstacle*> obstacles;
    TrafficLight* trafficLight;
};

#endif