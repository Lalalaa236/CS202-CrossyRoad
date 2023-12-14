#include "lane.h"
#include "GameSettings.h"
#include "animal/Bird.h"
#include "animal/Cat.h"
#include "animal/Dog.h"
#include "animal/Rabbit.h"
#include "animal/Tiger.h"
#include "Vehicle/Bike.h"
#include "Vehicle/Cab.h"
#include "Vehicle/Car.h"
#include "Vehicle/Truck.h"
#include "Vehicle/Taxi.h"
#include "Vehicle/Train.h"
#include <algorithm>
#include <iostream>
#include <vector>

Lane::Lane(float y, float mapSpeed, int currentScore) : y(y), mapSpeed(mapSpeed) {
    float trafficLight_x = settings::SCREEN_WIDTH - 5 - 50;
    randomSpeed = GetRandomValue(3.5f, 6.5f);
    direction = rand() % 2;

    // From right to left direction
    // Changing the speed and the position of the traffic light
    if (direction == 0) {
        randomSpeed = -randomSpeed;
        trafficLight_x = 5;
    }

    static int cnt = 0;
    int random = rand() % 3;

    switch (random) {
    case 0:
        if (cnt == 5) {
            texture = &TextureHolder::getHolder().get(Textures::GRASS);
            trafficLight = nullptr;
            cnt = 0;
            laneType = LaneType::GRASS;
        }
        else {
            texture = &TextureHolder::getHolder().get(Textures::ROAD);
            trafficLight = new TrafficLight(trafficLight_x, this->y - 25);
            cnt++;
            laneType = LaneType::ROAD;
        }
        break;
    case 1:
        if (cnt == 3) {
            texture = &TextureHolder::getHolder().get(Textures::ROAD);
            trafficLight = new TrafficLight(trafficLight_x, this->y - 25);
            cnt = 0;
            laneType = LaneType::ROAD;
        }
        else {
            texture = &TextureHolder::getHolder().get(Textures::GRASS);
            trafficLight = nullptr;
            cnt++;
            laneType = LaneType::GRASS;
        }
        break;
    case 2:
        texture = &TextureHolder::getHolder().get(Textures::RAILWAY);
        trafficLight = new TrafficLight(trafficLight_x, this->y - 25);
        laneType = LaneType::RAILWAY;
        break;
    default:
        texture = nullptr;
        trafficLight = nullptr;
        break;
    }

    int randomObstacle = rand() % 5;

    if(laneType == LaneType::RAILWAY)
        obstacleType = ObstacleType::Train;
    else if(laneType == LaneType::GRASS)
        obstacleType = (ObstacleType)randomObstacle;
    else
        obstacleType = (ObstacleType)(randomObstacle + 5);

    addObstacleByScore(currentScore);
}

Lane::~Lane() {
    while (obstacles.size()) {
        delete obstacles.front();
        obstacles.pop_front();
    }

    delete trafficLight;
}

Lane::Lane(float y, float mapSpeed, LaneType laneType, int numObstacles, ObstacleType ObstacleType) : y(y), mapSpeed(mapSpeed), laneType(laneType), obstacleType(ObstacleType) {
    float trafficLight_x = 5;
    randomSpeed = GetRandomValue(3.5f, 6.5f);
    direction = rand() % 2;

    if (direction == 0) {
        randomSpeed = -randomSpeed;
        trafficLight_x = settings::SCREEN_WIDTH - 5 - 50;
    }

    switch (laneType) {
    case LaneType::GRASS:
        texture = &TextureHolder::getHolder().get(Textures::GRASS);
        trafficLight = nullptr;
        break;
    case LaneType::ROAD:
        texture = &TextureHolder::getHolder().get(Textures::ROAD);
        trafficLight = new TrafficLight(trafficLight_x, this->y - 25);
        break;
    case LaneType::RAILWAY:
        texture = &TextureHolder::getHolder().get(Textures::RAILWAY);
        trafficLight = new TrafficLight(trafficLight_x, this->y - 25);
        break;
    default:
        texture = nullptr;
        trafficLight = nullptr;
        break;
    }

    addObstacle(numObstacles);
}

void Lane::addObstacle() {
    int r = rand() % 4;
    addObstacle(r);
}

void Lane::addObstacle(int numObstacle, float speedScale) {
    if (numObstacle <= 0) return;

    const int numPosition = numObstacle << 1; // numObstacle * 2
    Obstacle* tmp = nullptr;
    int i;
    float x;
    float distance = (1.0 * settings::SCREEN_WIDTH / numPosition);
    std::vector<float> distances;

    // Generate random distances
    for (i = 1; i <= numPosition; i++)
        distances.push_back(distance * (i - 1));
    std::random_shuffle(distances.begin(), distances.end());

    // Generate random obstacles
    for (i = 1; i <= numObstacle; i++) {
        x = distances[i - 1];
        obstacles.push_back(createObstacle(x, this->y, randomSpeed * speedScale));
    }

}

void Lane::addObstacleByScore(int laneScore) {
    int maxObstacles, minObstacles, numObstacles;
    float speedScale = 0.75f;

    // Generate depends on laneScore
    speedScale = speedScale + std::min(1.5f, laneScore / 50.0f); // Max speedScale = 2.5f
    maxObstacles = std::min(laneScore / 35 + 1, 6);
    minObstacles = std::min(laneScore / 75, 2);
    numObstacles = (rand() % (maxObstacles - minObstacles + 1)) + minObstacles;

    // Generate random obstacles
    addObstacle(numObstacles, speedScale);
}


void Lane::draw() {
    DrawTextureEx(*texture, { 0, y }, 0, 1, WHITE);

    if (trafficLight) {
        trafficLight->setY(y - 25);
        trafficLight->draw();
    }

    for (auto obstacle : obstacles) {
        obstacle->draw();
    }

    // static int i = 0;
}
void Lane::setY(float y) {
    this->y = y;
}

float Lane::getY() const {
    return y;
}

void Lane::update() {
    if (trafficLight)
        trafficLight->update();

    for (auto obstacle : obstacles)
        obstacle->update(this->getY());

    if(obstacles.size() > 0 && trafficLight)
    {
        if(trafficLight->getIsChanged())
        {
            if(!trafficLight->getLightState())
            {
                if(obstacles.front()->getUSpeed() & 0x80000000)
                    for (auto obstacle : obstacles)
                        obstacle->setSpeed(-0.0f);
                else
                    for (auto obstacle : obstacles)
                        obstacle->setSpeed(+0.0f);
            }
            else
            {
                for (auto obstacle : obstacles)
                    obstacle->setSpeed(randomSpeed);
            }  
        }
    }
}

void Lane::setSpeed(float mapSpeed) {
    this->mapSpeed = mapSpeed;
}

bool Lane::CheckCollisionPlayer(Rectangle playerBoxCollision) {
    for (auto obstacle : obstacles) {
        if (CheckCollisionRecs(obstacle->getBoxCollision(), playerBoxCollision))
            return true;
    }

    return false;
}

/// @brief Return a pointer to a randomly generated obstacle
/// @param safeLane 
/// @param x 
/// @param y 
/// @param speed 
/// @return Obstacle*
Obstacle* Lane::createObstacle(float x, float y, float speed) {
    int randomType;
    Obstacle* tmp = nullptr;

    switch(obstacleType) {
        case(ObstacleType::Bird):
            tmp = new Bird({x, y}, speed);
            break;
        case(ObstacleType::Cat):
            tmp = new Cat({x, y}, speed);
            break;
        case(ObstacleType::Dog):
            tmp = new Dog({x, y}, speed);
            break;
        case(ObstacleType::Rabbit):
            tmp = new Rabbit({x, y}, speed);
            break;
        case(ObstacleType::Tiger):
            tmp = new Tiger({x, y}, speed);
            break;
        case(ObstacleType::Bike):
            tmp = new Bike({x, y}, speed);
            break;
        case(ObstacleType::Cab):
            tmp = new Cab({x, y}, speed);
            break;
        case(ObstacleType::Car):
            tmp = new Car({x, y}, speed);
            break;
        case(ObstacleType::Truck):
            tmp = new Truck({x, y}, speed);
            break;
        case(ObstacleType::Taxi):
            tmp = new Taxi({x, y}, speed);
            break;
        case(ObstacleType::Train):
            tmp = new Train({x, y}, speed);
            break;
        default:
            break;
    }

    return tmp;
}