#include "lane.h"
#include "Bike.h"
#include "Bird.h"
#include "Cab.h"
#include "Car.h"
#include "Cat.h"
#include "Dog.h"
#include "GameSettings.h"
#include "Rabbit.h"
#include "Taxi.h"
#include "Tiger.h"
#include "Train.h"
#include "Truck.h"

#include <algorithm>
#include <iostream>
#include <vector>

Lane::Lane(float y, float mapSpeed, int currentScore) : y(y), mapSpeed(mapSpeed) {
    float trafficLight_x = settings::SCREEN_WIDTH - 5 - 50;
    randomSpeed = GetRandomValue(3.0f, 5.0f);
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
            isSafe = 1;
        }
        else {
            texture = &TextureHolder::getHolder().get(Textures::ROAD);
            trafficLight = new TrafficLight(trafficLight_x, this->y - 25);
            cnt++;
            isSafe = 0;
        }
        break;
    case 1:
        if (cnt == 3) {
            texture = &TextureHolder::getHolder().get(Textures::ROAD);
            trafficLight = new TrafficLight(trafficLight_x, this->y - 25);
            cnt = 0;
            isSafe = 0;
        }
        else {
            texture = &TextureHolder::getHolder().get(Textures::GRASS);
            trafficLight = nullptr;
            cnt++;
            isSafe = 1;
        }
        break;
    case 2:
        texture = &TextureHolder::getHolder().get(Textures::RAILWAY);
        trafficLight = new TrafficLight(trafficLight_x, this->y - 25);
        isSafe = 2;
        break;
    default:
        texture = nullptr;
        trafficLight = nullptr;
        break;
    }

    addObstacleByScore(currentScore);
}

Lane::~Lane() {
    while (obstacles.size()) {
        delete obstacles.front();
        obstacles.pop_front();
    }

    delete trafficLight;
}

Lane::Lane(float y, float mapSpeed, LaneType laneType, int numObstacles) : y(y), mapSpeed(mapSpeed) {
    float trafficLight_x = 5;
    randomSpeed = GetRandomValue(3.0f, 5.0f);
    direction = rand() % 2;

    if (direction == 0) {
        randomSpeed = -randomSpeed;
        trafficLight_x = settings::SCREEN_WIDTH - 5 - 50;
    }

    switch (laneType) {
    case LaneType::GRASS:
        texture = &TextureHolder::getHolder().get(Textures::GRASS);
        trafficLight = nullptr;
        isSafe = 1;
        break;
    case LaneType::ROAD:
        texture = &TextureHolder::getHolder().get(Textures::ROAD);
        trafficLight = new TrafficLight(trafficLight_x, this->y - 25);
        isSafe = 0;
        break;
    case LaneType::RAILWAY:
        texture = &TextureHolder::getHolder().get(Textures::RAILWAY);
        trafficLight = new TrafficLight(trafficLight_x, this->y - 25);
        isSafe = 2;
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
    if (numObstacle <= 0)
        return;

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
        obstacles.push_back(createObstacle(isSafe, x, this->y, randomSpeed * speedScale));
    }
}

void Lane::addObstacleByScore(int laneScore) {
    int maxObstacles, minObstacles, numObstacles;
    float speedScale = 0.75f;

    // Generate depends on laneScore
    speedScale = speedScale + std::min(1.5f, laneScore / 50.0f); // Max speedScale = 2.5f
    maxObstacles = std::min(laneScore / 30 + 2, 6);
    minObstacles = std::min(laneScore / 60, 2);

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
Obstacle* createObstacle(int safeLane, float x, float y, float speed) {
    int randomType;
    Obstacle* tmp = nullptr;

    if (safeLane == 2) {
        tmp = new Train({ 0, y }, speed);
    }

    if (safeLane == 1) {
        randomType = rand() % 5;

        switch (randomType) {
        case 0:
            tmp = new Bird({ x, y }, speed);
            break;
        case 1:
            tmp = new Cat({ x, y }, speed);
            break;
        case 2:
            tmp = new Dog({ x, y }, speed);
            break;
        case 3:
            tmp = new Tiger({ x, y }, speed);
            break;
        case 4:
            tmp = new Rabbit({ x, y }, speed);
            break;
        default:
            break;
        }
    }
    if (safeLane == 0) {
        randomType = rand() % 5;

        switch (randomType) {
        case 0:
            tmp = new Bike({ x, y - 15 }, speed);
            break;
        case 1:
            tmp = new Cab({ x, y }, speed);
            break;
        case 2:
            tmp = new Car({ x, y + 10 }, speed);
            break;
        case 3:
            tmp = new Truck({ x, y - 6 }, speed);
            break;
        case 4:
            tmp = new Taxi({ x, y + 20 }, speed);
            break;
        }
    }

    return tmp;
}
