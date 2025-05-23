#include "lane.h"
#include "Animal.h"
#include "GameSettings.h"
#include "Vehicle.h"
#include "random.h"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

static int preLane = 0;

Lane::Lane(float y, float mapSpeed, int currentScore) : y(y), mapSpeed(mapSpeed) {
    float trafficLight_x = settings::SCREEN_WIDTH - 5 - 50;
    randomSpeed = Random::getInstance().nextDouble(3.0f, 5.0f);
    direction = Random::getInstance().nextInt() % 2;

    // From right to left direction
    // Changing the speed and the position of the traffic light
    if (direction == 0) {
        randomSpeed = -randomSpeed;
        trafficLight_x = 5;
    }

    static int cnt;
    static int consecutiveRailways = 0;
    int random = Random::getInstance().nextInt() % 4; //just road and grass

    if (currentScore >= 40) {
        random = Random::getInstance().nextInt() % 5;
    }
    else if (currentScore >= 80) {
        random = Random::getInstance().nextInt() % 6;
    }else if (currentScore >= 120) random = Random::getInstance().nextInt() % 7;
    //std::cout << "Random: " << random << std::endl;

    switch (random) {
    case 0:
    case 1:
        if (preLane == 1) cnt = 0; //if preLane is grass
        if (cnt == 5) {
            texture = &TextureHolder::getHolder().get(Textures::GRASS);
            laneType = LaneType::GRASS;
            trafficLight = nullptr;
            cnt = 0;
            consecutiveRailways = 0;
        }
        else {
            texture = &TextureHolder::getHolder().get(Textures::ROAD);
            laneType = LaneType::ROAD;
            trafficLight = new TrafficLight(trafficLight_x, this->y - 25, TrafficLight::Type::ROAD);
            cnt++;
            consecutiveRailways = 0;
        }
        break;
    case 2:
    case 3:
        if (preLane == 2) cnt = 0;//if preLane is Road
        if (cnt == 3) {
            texture = &TextureHolder::getHolder().get(Textures::ROAD);
            laneType = LaneType::ROAD;
            trafficLight = new TrafficLight(trafficLight_x, this->y - 25, TrafficLight::Type::ROAD);
            cnt = 0;
            consecutiveRailways = 0;
        }
        else {
            texture = &TextureHolder::getHolder().get(Textures::GRASS);
            laneType = LaneType::GRASS;
            trafficLight = nullptr;
            cnt++;
            consecutiveRailways = 0;
        }
        break;
    case 4:
    case 5:
    case 6:
        if (consecutiveRailways >= 2) { // Limit consecutive railway lanes
            texture = &TextureHolder::getHolder().get(Textures::GRASS);
            laneType = LaneType::GRASS;
            trafficLight = nullptr;
            cnt = 0;
            consecutiveRailways = 0;
        }
        else {
            texture = &TextureHolder::getHolder().get(Textures::RAILWAY);
            trafficLight = new TrafficLight(trafficLight_x, this->y - 25, TrafficLight::Type::RAILWAY);
            laneType = LaneType::RAILWAY;
            cnt = 0;
            consecutiveRailways++;
        }
        break;
    default:
        texture = nullptr;
        trafficLight = nullptr;
        break;
    }
    if (laneType == LaneType::ROAD){
        preLane = 2;
    }
    if (laneType == LaneType::GRASS){
        preLane = 1;
    }
    int randomObstacle = Random::getInstance().nextInt() % 5;

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
    direction = Random::getInstance().nextInt() % 2;

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
    case LaneType::DESERT_1:
        texture = &TextureHolder::getHolder().get(Textures::DESERT_1);
        trafficLight = nullptr;
        break;
    case LaneType::DESERT_2:
        texture = &TextureHolder::getHolder().get(Textures::DESERT_2);
        trafficLight = nullptr;
        break;
    default:
        texture = nullptr;
        trafficLight = nullptr;
        break;
    }

    addObstacle(numObstacles);
}

void Lane::addObstacle() {
    int r = Random::getInstance().nextInt(0, 3);
    addObstacle(r);
}

void Lane::addObstacle(int numObstacle, float speedScale) {
    if (numObstacle <= 0)
        return;

    if (laneType == LaneType::RAILWAY) {
        if (!direction)
            obstacles.push_back(createObstacle(obstacleType, settings::SCREEN_WIDTH, this->y, randomSpeed * speedScale));
        else
            obstacles.push_back(createObstacle(obstacleType, 0, this->y, randomSpeed * speedScale));
        obstacles.front()->resetPos();
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
    float speedScale = 1.0f;

    // Generate depends on laneScore
    speedScale = std::min(2.5f, 0.8f + laneScore / 150.0f); // Max speedScale = 2.5f
    minObstacles = 0;
    maxObstacles = std::min(laneScore / 30 + 2, 4);
    // nextInt max
    numObstacles = Random::getInstance().nextInt(minObstacles, maxObstacles);
    numObstacles = std::max(numObstacles, Random::getInstance().nextInt(minObstacles, maxObstacles));

    if (numObstacles < 0 || numObstacles > 4)
        throw std::runtime_error("Invalid number of obstacles");

    if (laneType == LaneType::RAILWAY) {
        numObstacles = 1;
        speedScale = 5.0f;
        randomSpeed *= speedScale;
    }
    else if (trafficLight && laneType == LaneType::ROAD) {
        double redTimer = trafficLight->getRedTimer();
        double greenTimer = trafficLight->getGreenTimer();
        double scaling = std::max(1.0f, std::min(speedScale, 1.5f));

        trafficLight->setTimer(redTimer / scaling, greenTimer * scaling);
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

    if (laneType == LaneType::RAILWAY && obstacles.front()->checkOutOfScreen() && !trafficLight->getLightState())
        trafficLight->setLightState(true);

    // if (!trafficLight->getIsChanged())
    //     return;

    if (!trafficLight->getLightState()) {
        if (laneType == LaneType::ROAD || laneType == LaneType::DESERT_2) {
            if (obstacles.front()->getSpeed() == +0.0f || obstacles.front()->getSpeed() == -0.0f)
                return;
            if (obstacles.front()->getUSpeed() & 0x80000000)
                for (auto obstacle : obstacles)
                    obstacle->setSpeed(-0.0f);
            else
                for (auto obstacle : obstacles)
                    obstacle->setSpeed(+0.0f);
        }
        else if (laneType == LaneType::RAILWAY) {
            if (obstacles.front()->getSpeed() == randomSpeed)
                return;
            for (auto obstacle : obstacles)
                obstacle->setSpeed(randomSpeed);
        }
    }
    else {
        if (laneType == LaneType::ROAD || laneType == LaneType::DESERT_2) {
            if (obstacles.front()->getSpeed() == randomSpeed)
                return;
            for (auto obstacle : obstacles)
                obstacle->setSpeed(randomSpeed);
        }
        else if (laneType == LaneType::RAILWAY) {
            if (obstacles.front()->getSpeed() == +0.0f || obstacles.front()->getSpeed() == -0.0f)
                return;
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
        if (CheckCollisionRecs(obstacle->getBoxCollision(), playerBoxCollision)) {
            return true;
        }
    }

    return false;
}

// [laneData] = [laneType] [laneSpeed] [lane.y] [laneDirection] [numObstacle] [obstacleData1] [obstacleData2] ... [obstacleDataN]
// [obstacleData] = [obstacleType] [obstacle.x]
std::string Lane::serializeData() {
    std::string serialized_data = "";
    int lType = static_cast<int>(laneType);

    serialized_data += std::to_string(lType) + " ";
    serialized_data += std::to_string(randomSpeed) + " ";
    serialized_data += std::to_string(y) + " ";
    serialized_data += std::to_string(direction) + " ";

    if (laneType != LaneType::GRASS) { // Add traffic timer
        serialized_data += std::to_string(trafficLight->getTimer()) + " ";
        serialized_data += std::to_string(trafficLight->getRedTimer()) + " ";
        serialized_data += std::to_string(trafficLight->getGreenTimer()) + " ";
        serialized_data += std::to_string(trafficLight->getLightState()) + " ";
    }

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

    iss >> lType >> randomSpeed >> y >> direction;
    laneType = LaneType(lType);

    if (laneType != LaneType::GRASS) { // Add traffic timer
        float timer, redTimer, greenTimer;
        bool lightState;
        iss >> timer >> redTimer >> greenTimer >> lightState;

        if (trafficLight) {
            trafficLight->setTimer(timer);
            trafficLight->setTimer(redTimer, greenTimer);
            trafficLight->setLightState(lightState);
        }
    }

    iss >> numObstacle;

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

Lane::LaneType Lane::getType() const {
    return laneType;
}