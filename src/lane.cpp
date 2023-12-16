#include "lane.h"
#include "GameSettings.h"
#include "Bird.h"
#include "Cat.h"
#include "Dog.h"
#include "Rabbit.h"
#include "Tiger.h"
#include "Bike.h"
#include "Cab.h"
#include "Car.h"
#include "Truck.h"
#include "Taxi.h"
#include "Train.h"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

Lane::Lane(float y, float mapSpeed, int currentScore) : y(y), mapSpeed(mapSpeed) {
    float trafficLight_x = settings::SCREEN_WIDTH - 5 - 50;
    randomSpeed = Random::getInstance().nextDouble(3.0f, 5.0f);
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
            trafficLight = new TrafficLight(trafficLight_x, this->y - 25, TrafficLight::Type::ROAD);
            cnt++;
            laneType = LaneType::ROAD;
        }
        break;
    case 1:
        if (cnt == 3) {
            texture = &TextureHolder::getHolder().get(Textures::ROAD);
            trafficLight = new TrafficLight(trafficLight_x, this->y - 25, TrafficLight::Type::ROAD);
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
        trafficLight = new TrafficLight(trafficLight_x, this->y - 25, TrafficLight::Type::RAILWAY);
        laneType = LaneType::RAILWAY;
        break;
    default:
        texture = nullptr;
        trafficLight = nullptr;
        break;
    }

    int randomObstacle = rand() % 5;

    if (laneType == LaneType::RAILWAY)
        obstacleType = ObstacleType::Train;
    else if (laneType == LaneType::GRASS)
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
    randomSpeed = Random::getInstance().nextDouble(3.0f, 5.0f);
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
        trafficLight = new TrafficLight(trafficLight_x, this->y - 25, TrafficLight::Type::ROAD);
        break;
    case LaneType::RAILWAY:
        texture = &TextureHolder::getHolder().get(Textures::RAILWAY);
        trafficLight = new TrafficLight(trafficLight_x, this->y - 25, TrafficLight::Type::RAILWAY);
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
    maxObstacles = std::min(laneScore / 30 + 2, 6);
    minObstacles = std::min(laneScore / 60, 2);

    numObstacles = Random::getInstance().nextInt(minObstacles, maxObstacles);

    // Generate random obstacles
    addObstacle(numObstacles, speedScale);
}

int Lane::obstacleType(Obstacle* obstacle) {
    if (dynamic_cast<Bike*>(obstacle))
        return 0;
    if (dynamic_cast<Cab*>(obstacle))
        return 1;
    if (dynamic_cast<Car*>(obstacle))
        return 2;
    if (dynamic_cast<Truck*>(obstacle))
        return 3;
    if (dynamic_cast<Taxi*>(obstacle))
        return 4;

    if (dynamic_cast<Bird*>(obstacle))
        return 5;
    if (dynamic_cast<Cat*>(obstacle))
        return 6;
    if (dynamic_cast<Dog*>(obstacle))
        return 7;
    if (dynamic_cast<Tiger*>(obstacle))
        return 8;
    if (dynamic_cast<Rabbit*>(obstacle))
        return 9;

    if (dynamic_cast<Train*>(obstacle))
        return 10;

    return -1;
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

    if (obstacles.size() > 0 && trafficLight)
    {
        if (trafficLight->getIsChanged())
        {
            if (!trafficLight->getLightState())
            {
                if (laneType == LaneType::ROAD)
                {
                    if (obstacles.front()->getUSpeed() & 0x80000000)
                        for (auto obstacle : obstacles)
                            obstacle->setSpeed(-0.0f);
                    else
                        for (auto obstacle : obstacles)
                            obstacle->setSpeed(+0.0f);
                }
                else if (laneType == LaneType::RAILWAY)
                {
                    for (auto obstacle : obstacles)
                        obstacle->setSpeed(randomSpeed);
                }
            }
            else
            {
                if (laneType == LaneType::ROAD)
                {
                    for (auto obstacle : obstacles)
                        obstacle->setSpeed(randomSpeed);
                }
                else if (laneType == LaneType::RAILWAY)
                {
                    if (obstacles.front()->getUSpeed() & 0x80000000)
                        for (auto obstacle : obstacles)
                            obstacle->setSpeed(-0.0f);
                    else
                        for (auto obstacle : obstacles)
                            obstacle->setSpeed(+0.0f);
                }
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

// [laneData] = [laneType] [laneSpeed] [lane.y] [laneDirection] [numObstacle] [obstacleData1] [obstacleData2] ... [obstacleDataN]
// [obstacleData] = [obstacleType] [obstacle.x]
std::string Lane::serializeData() {
    std::string serialized_data = "";

    serialized_data += std::to_string(static_cast<int>(isSafe)) + " ";
    serialized_data += std::to_string(randomSpeed) + " ";
    serialized_data += std::to_string(y) + " ";
    serialized_data += std::to_string(direction) + " ";
    serialized_data += std::to_string(obstacles.size()) + " ";

    for (auto obstacle : obstacles) {
        std::string obstacleData = "";

        obstacleData += std::to_string(obstacleType(obstacle)) + " ";
        obstacleData += std::to_string(obstacle->getPos().x) + " ";

        serialized_data += obstacleData;
    }

    return serialized_data;
}

void Lane::loadSerializedData(const std::string& serialized_data) {
    std::istringstream iss(serialized_data);
    std::string tmp;
    int numObstacle, obstacleType;
    float x;

    iss >> isSafe >> randomSpeed >> y >> direction >> numObstacle;

    for (int i = 0; i < numObstacle; i++) {
        iss >> obstacleType >> x;
        obstacles.push_back(createObstacle(obstacleType, x, y, randomSpeed));
    }
}

Obstacle* createObstacle(int obstacleType, float x, float y, float speed) {
    Obstacle* tmp = nullptr;

    switch (obstacleType) {
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
    case 5:
        tmp = new Bird({ x, y }, speed);
        break;
    case 6:
        tmp = new Cat({ x, y }, speed);
        break;
    case 7:
        tmp = new Dog({ x, y }, speed);
        break;
    case 8:
        tmp = new Tiger({ x, y }, speed);
        break;
    case 9:
        tmp = new Rabbit({ x, y }, speed);
        break;
    case 10:
        tmp = new Train({ 0, y }, speed);
        break;
    default:
        throw std::runtime_error("Invalid obstacle type");
        break;
    }

    return tmp;
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

    switch (obstacleType) {
    case(ObstacleType::Bird):
        tmp = new Bird({ x, y }, speed);
        break;
    case(ObstacleType::Cat):
        tmp = new Cat({ x, y }, speed);
        break;
    case(ObstacleType::Dog):
        tmp = new Dog({ x, y }, speed);
        break;
    case(ObstacleType::Rabbit):
        tmp = new Rabbit({ x, y }, speed);
        break;
    case(ObstacleType::Tiger):
        tmp = new Tiger({ x, y }, speed);
        break;
    case(ObstacleType::Bike):
        tmp = new Bike({ x, y }, speed);
        break;
    case(ObstacleType::Cab):
        tmp = new Cab({ x, y }, speed);
        break;
    case(ObstacleType::Car):
        tmp = new Car({ x, y }, speed);
        break;
    case(ObstacleType::Truck):
        tmp = new Truck({ x, y }, speed);
        break;
    case(ObstacleType::Taxi):
        tmp = new Taxi({ x, y }, speed);
        break;
    case(ObstacleType::Train):
        tmp = new Train({ x, y }, speed);
        break;
    default:
        break;
    }

    return tmp;
}