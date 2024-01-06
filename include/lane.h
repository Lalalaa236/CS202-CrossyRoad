#ifndef LANE_H
#define LANE_H

#include "Obstacle.h"
#include "TextureHolder.h"
#include "trafficlight.h"
#include <deque>

class Lane {
public:
    enum class ObstacleType : int {
        Bird = 0,
        Cat = 1,
        Dog = 2,
        Rabbit = 3,
        Tiger = 4,
        Bike = 5,
        Cab = 6,
        Car = 7,
        Truck = 8,
        Taxi = 9,
        Train = 10,
        None = -1
    };
    enum class LaneType : int { ROAD = 0, GRASS = 1, RAILWAY = 2, DESERT_1 = 3, DESERT_2 = 4 };
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



