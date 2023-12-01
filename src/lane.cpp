#include "lane.h"
#include "GameSettings.h"
#include "animal/Bird.h"
#include "animal/Cat.h"
#include "animal/Dog.h"
#include "animal/Rabbit.h"
#include "animal/Tiger.h"

#include <iostream>
#include <vector>

Lane::Lane(float y, float mapSpeed) : y(y), mapSpeed(mapSpeed) {
    randomSpeed = GetRandomValue(3.0f, 6.0f);

    static int cnt = 0;
    int random = rand() % 2;
    switch (random) {
    case 0:
        if (cnt == 5) {
            texture = &TextureHolder::getHolder().get(Textures::GRASS);
            trafficLight = nullptr;
            cnt = 0;
            isSafe = true;
        } else {
            texture = &TextureHolder::getHolder().get(Textures::ROAD);
            trafficLight = new TrafficLight(5, this->y - 25);
            cnt++;
            isSafe = false;
        }
        break;
    case 1:
        if (cnt == 3) {
            texture = &TextureHolder::getHolder().get(Textures::ROAD);
            trafficLight = new TrafficLight(5, this->y - 25);
            cnt = 0;
            isSafe = false;
        } else {
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

Lane::Lane(float y, float mapSpeed, LaneType laneType, int numObstacles)
    : y(y), mapSpeed(mapSpeed) {
    randomSpeed = GetRandomValue(1.0f, 3.0f);
    switch (laneType) {
    case LaneType::GRASS:
        texture = &TextureHolder::getHolder().get(Textures::GRASS);
        trafficLight = nullptr;
        isSafe = true;
        break;
    case LaneType::ROAD:
        texture = &TextureHolder::getHolder().get(Textures::ROAD);
        trafficLight = new TrafficLight(5, this->y - 25);
        isSafe = false;
        break;
    default:
        texture = nullptr;
        trafficLight = nullptr;
        break;
    }

    addObstacle(numObstacles);
    // std::cout << "lmao" << std::endl;
}

void Lane::addObstacle() {
    int r = rand() % 5;
    if (r == 0)
        return;

    if (isSafe) {
        Obstacle *tmp = nullptr;
        float distance = (settings::SCREEN_WIDTH / r * 1.0);

        for (int i = 1; i <= r; i++) {
            int randomType = rand() % 5;
            float x = distance * (i - 1);

            switch (randomType) {
            case 0:
                tmp = new Bird({x, this->y}, randomSpeed);
                break;
            case 1:
                tmp = new Cat({x, this->y}, randomSpeed);
                break;
            case 2:
                tmp = new Dog({x, this->y}, randomSpeed);
                break;
            case 3:
                tmp = new Tiger({x, this->y}, randomSpeed);
                break;
            case 4:
                tmp = new Rabbit({x, this->y}, randomSpeed);
                break;
            default:
                break;
            }

            if (tmp)
                obstacles.push_back(tmp);
        }
    }
}

void Lane::addObstacle(int n) {
    if (n == 0)
        return;
    float dis = (settings::SCREEN_WIDTH / n * 1.0);
    for (int i = 1; i <= n; ++i) {
        Obstacle *tmp = nullptr;
        int randomType = rand() % 5;
        switch (randomType) {
        case 0:
            tmp = new Bird({dis * (i - 1), this->y}, randomSpeed);
            break;
        case 1:
            tmp = new Cat({dis * (i - 1), this->y}, randomSpeed);
            break;
        case 2:
            tmp = new Dog({dis * (i - 1), this->y}, randomSpeed);
            break;
        case 3:
            tmp = new Tiger({dis * (i - 1), this->y}, randomSpeed);
            break;
        case 4:
            tmp = new Rabbit({dis * (i - 1), this->y}, randomSpeed);
            break;
        default:
            break;
        }
        if (tmp)
            obstacles.push_back(tmp);
    }
}

void Lane::draw() {
    DrawTextureEx(*texture, {0, y}, 0, 1, WHITE);
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

bool Lane::CheckCollisionPLayer(Rectangle playerBoxCollision) {
    for (auto obstacle : obstacles) {
        if (CheckCollisionRecs(obstacle->getBoxCollision(), playerBoxCollision))
            return true;
    }
    return false;
}