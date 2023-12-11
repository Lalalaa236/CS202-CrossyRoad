#ifndef LANE_H
#define LANE_H

#include "Obstacle.h"
#include "TextureHolder.h"
#include "trafficlight.h"
#include <deque>

class Lane {
private:
    float randomSpeed;
    const Texture2D* texture;
    float y;
    float mapSpeed;
    std::deque<Obstacle*> obstacles;
    TrafficLight* trafficLight;
    int isSafe;
    bool direction; // true = right, false = left

public:
    enum LaneType { ROAD, GRASS, RAILWAY};
    Lane(float y, float mapSpeed, int currentScore = 0);
    Lane(float y, float mapSpeed, LaneType laneType, int numObstacles);
    ~Lane();

    void setY(float y);
    float getY() const;
    void setSpeed(float mapSpeed);

    void addObstacle();
    void addObstacle(int numObstacle, float speedScale = 1.0f);
    void addObstacleByScore(int laneScore);
    void draw();
    void update();
    bool CheckCollisionPlayer(Rectangle playerBoxCollision);
};

Obstacle* createObstacle(int safeLane, float x, float y, float speed);

#endif