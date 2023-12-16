#ifndef LANE_H
#define LANE_H

#include "Obstacle.h"
#include "TextureHolder.h"
#include "trafficlight.h"
#include <deque>

class Lane {
public:
    enum class ObstacleType 
    { 
        Bird,
        Cat, 
        Dog,
        Rabbit,
        Tiger,
        Bike,
        Cab,
        Car,
        Truck,
        Taxi,
        Train,
        None
    };
    enum class LaneType { ROAD, GRASS, RAILWAY};
    Lane(float y, float mapSpeed, int currentScore = 0);
    Lane(float y, float mapSpeed, LaneType laneType, int numObstacles, ObstacleType obstacleType);
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
    
    std::string serializeData();
    void loadSerializedData(const std::string& serialized_data);
    
private:
    float randomSpeed;
    const Texture2D* texture;
    float y;
    float mapSpeed;
    std::deque<Obstacle*> obstacles;
    TrafficLight* trafficLight;
    bool direction; // true = right, false = left
    ObstacleType obstacleType;
    LaneType laneType;

    Obstacle* createObstacle(float x, float y, float speed);
};

Obstacle* createObstacle(int obstacleType, float x, float y, float speed);
Obstacle* randomObstacle(int safeLane, float x, float y, float speed);

#endif



