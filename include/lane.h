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
    enum class LaneType { ROAD, GRASS, RAILWAY,DESERT_1,DESERT_2};
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
    void loadSerializedData(const std::string& serialized_data);\
    LaneType getType() const;
private:
    float randomSpeed;
    float mapSpeed;
    float y;
    const Texture2D* texture;

    LaneType laneType;
    ObstacleType obstacleType;
    std::deque<Obstacle*> obstacles;
    TrafficLight* trafficLight;
    bool direction; // true = right, false = left

    Obstacle* createObstacle(ObstacleType id, float x, float y, float speed);
};

#endif



