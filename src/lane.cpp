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
#include <algorithm>
#include <iostream>
#include <vector>

Lane::Lane(float y, float mapSpeed) : y(y), mapSpeed(mapSpeed) {
    float trafficLight_x = 5;
    randomSpeed = GetRandomValue(3.0f, 6.0f);
    direction = rand() % 2;

    // From right to left direction
    // Changing the speed and the position of the traffic light
    if (direction == 0) {
        randomSpeed = -randomSpeed;
        trafficLight_x = settings::SCREEN_WIDTH - 5 - 50;
    }

    static int cnt = 0;
    int random = rand() % 2;

    switch (random) {
    case 0:
        if (cnt == 5) {
            texture = &TextureHolder::getHolder().get(Textures::GRASS);
            trafficLight = nullptr;
            cnt = 0;
            isSafe = true;
        }
        else {
            texture = &TextureHolder::getHolder().get(Textures::ROAD);
            trafficLight = new TrafficLight(trafficLight_x, this->y - 25);
            cnt++;
            isSafe = false;
        }
        break;
    case 1:
        if (cnt == 3) {
            texture = &TextureHolder::getHolder().get(Textures::ROAD);
            trafficLight = new TrafficLight(trafficLight_x, this->y - 25);
            cnt = 0;
            isSafe = false;
        }
        else {
            texture = &TextureHolder::getHolder().get(Textures::GRASS);
            trafficLight = nullptr;
            cnt++;
            isSafe = true;
        }
        break;
    default:
        texture = nullptr;
        trafficLight = nullptr;
        break;
    }

    addObstacle();
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
    randomSpeed = GetRandomValue(1.0f, 3.0f);
    direction = rand() % 2;

    if (direction == 0) {
        randomSpeed = -randomSpeed;
        trafficLight_x = settings::SCREEN_WIDTH - 5 - 50;
    }

    switch (laneType) {
    case LaneType::GRASS:
        texture = &TextureHolder::getHolder().get(Textures::GRASS);
        trafficLight = nullptr;
        isSafe = true;
        break;
    case LaneType::ROAD:
        texture = &TextureHolder::getHolder().get(Textures::ROAD);
        trafficLight = new TrafficLight(trafficLight_x, this->y - 25);
        isSafe = false;
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

void Lane::addObstacle(int n) {
    if (n <= 0) return;

    Obstacle* tmp = nullptr;
    int randomType, i;
    float x;
    float distance = (1.0 * settings::SCREEN_WIDTH / (n << 1));
    std::vector<float> distances;

    // Generate random distances
    for (i = 1; i <= 2 * n; i++)
        distances.push_back(distance * (i - 1));
    std::random_shuffle(distances.begin(), distances.end());

    if (isSafe) {
        for (i = 1; i <= n; i++) {
            randomType = rand() % 5;
            x = distances[i - 1];

            switch (randomType) {
            case 0:
                tmp = new Bird({ x, this->y }, randomSpeed);
                break;
            case 1:
                tmp = new Cat({ x, this->y }, randomSpeed);
                break;
            case 2:
                tmp = new Dog({ x, this->y }, randomSpeed);
                break;
            case 3:
                tmp = new Tiger({ x, this->y }, randomSpeed);
                break;
            case 4:
                tmp = new Rabbit({ x, this->y }, randomSpeed);
                break;
            default:
                break;
            }

            if (tmp)
                obstacles.push_back(tmp);
        }
    }
    else {
        for (i = 1; i <= n; i++) {
            randomType = rand() % 5;
            x = distances[i - 1];

            switch (randomType) {
            case 0:
                tmp = new Bike({ x, this->y - 35 }, randomSpeed);
                break;
            case 1:
                tmp = new Cab({ x, this->y }, randomSpeed);
                break;
            case 2:
                tmp = new Car({ x, this->y + 10 }, randomSpeed);
                break;
            case 3:
                tmp = new Truck({ x, this->y - 10 }, randomSpeed);
                break;
            case 4:
                tmp = new Taxi({ x, this->y + 20 }, randomSpeed);
                break;
            }

            if (tmp)
                obstacles.push_back(tmp);
        }
    }
}

void Lane::draw() {
    DrawTextureEx(*texture, { 0, y }, 0, 1, WHITE);
    // DrawRectangleLinesEx({0, y, 1511, 95}, 2, BLACK);
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

    for (auto obstacle : obstacles) {
        obstacle->update(this->getY());
    }
    // static int i = 0;
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