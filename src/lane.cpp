#include "lane.h"
#include "Animal.h"
#include "GameSettings.h"
#include "Vehicle.h"
#include "random.h"

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

Lane::Lane(float y, float mapSpeed, LaneType laneType, int numObstacles, ObstacleType ObstacleType)
    : y(y), mapSpeed(mapSpeed), laneType(laneType), obstacleType(ObstacleType) {
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
    if(laneType == LaneType::RAILWAY)
    {
        if(direction)
            obstacles.push_back(createObstacle(obstacleType, settings::SCREEN_WIDTH, this->y, randomSpeed * speedScale));
        else
            obstacles.push_back(createObstacle(obstacleType, 0, this->y, randomSpeed * speedScale));
        return;
    }

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
        obstacles.push_back(createObstacle(obstacleType, x, this->y, randomSpeed * speedScale));
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

    if (laneType == LaneType::RAILWAY) {
        numObstacles = 1;
        speedScale = 5.0f;
        randomSpeed *= speedScale;
    }

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

    if (!(obstacles.size() > 0 && trafficLight))
        return;
    
    if(laneType == LaneType::RAILWAY)
    {
        if(obstacles.front()->checkOutOfScreen())
            trafficLight->setLightState(true);
    }

    if (!trafficLight->getIsChanged())
        return;

    if (!trafficLight->getLightState()) {
        if (laneType == LaneType::ROAD) {
            if (obstacles.front()->getUSpeed() & 0x80000000)
                for (auto obstacle : obstacles)
                    obstacle->setSpeed(-0.0f);
            else
                for (auto obstacle : obstacles)
                    obstacle->setSpeed(+0.0f);
        }
        else if (laneType == LaneType::RAILWAY) {
            for (auto obstacle : obstacles)
                obstacle->setSpeed(randomSpeed);
        }
    }
    else {
        if (laneType == LaneType::ROAD) {
            for (auto obstacle : obstacles)
                obstacle->setSpeed(randomSpeed);
        }
        else if (laneType == LaneType::RAILWAY) {
            if (obstacles.front()->getUSpeed() & 0x80000000)
                for (auto obstacle : obstacles)
                    obstacle->setSpeed(-0.0f);
            else
                for (auto obstacle : obstacles)
                    obstacle->setSpeed(+0.0f);
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

    serialized_data += std::to_string(int(laneType)) + " ";
    serialized_data += std::to_string(randomSpeed) + " ";
    serialized_data += std::to_string(y) + " ";
    serialized_data += std::to_string(direction) + " ";
    serialized_data += std::to_string(obstacles.size()) + " ";

    for (auto obstacle : obstacles) {
        std::string obstacleData = "";

        obstacleData += std::to_string(int(obstacleType)) + " ";
        obstacleData += std::to_string(obstacle->getPos().x) + " ";

        serialized_data += obstacleData;
    }

    return serialized_data;
}

void Lane::loadSerializedData(const std::string& serialized_data) {
    std::istringstream iss(serialized_data);
    std::string tmp;
    int numObstacle, oType, lType;
    float x;

    iss >> lType >> randomSpeed >> y >> direction >> numObstacle;
    laneType = LaneType(lType);

    for (int i = 0; i < numObstacle; i++) {
        iss >> oType >> x;
        obstacleType = ObstacleType(oType);
        obstacles.push_back(createObstacle(obstacleType, x, y, randomSpeed));
    }
}

Obstacle* Lane::createObstacle(ObstacleType id, float x, float y, float speed) {
    switch (id) {
    case ObstacleType::Bird:
        return new Bird({ x, y }, speed);
    case ObstacleType::Cat:
        return new Cat({ x, y }, speed);
    case ObstacleType::Dog:
        return new Dog({ x, y }, speed);
    case ObstacleType::Rabbit:
        return new Rabbit({ x, y }, speed);
    case ObstacleType::Tiger:
        return new Tiger({ x, y }, speed);
    case ObstacleType::Bike:
        return new Bike({ x, y }, speed);
    case ObstacleType::Cab:
        return new Cab({ x, y }, speed);
    case ObstacleType::Car:
        return new Car({ x, y }, speed);
    case ObstacleType::Truck:
        return new Truck({ x, y }, speed);
    case ObstacleType::Taxi:
        return new Taxi({ x, y }, speed);
    case ObstacleType::Train:
        return new Train({ x, y }, speed);
    default:
        throw std::runtime_error("Invalid obstacle type");
    }
}
