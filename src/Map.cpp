#include "Map.h"
#include <iostream>

Map::Map(float speed) : speed(speed) {
    int j = rand() % 4 + 1;
    int i = 0;
    // std::cout << "j = " << j << std::endl;
    for (; i < 12 - j; ++i) {
        Lane *lane = new Lane(-158.0f + i * 95.0f, speed);
        lanes.push_back(lane);
    }
    for (int k = 1; k <= j; ++k) {
        Lane *lane = new Lane(-158.0f + i * 95.0f, speed, Lane::LaneType::GRASS, 0);
        lanes.push_back(lane);
        ++i;
    }
}

void Map::draw() {
    for (auto lane : lanes) {
        lane->draw();
    }
    // static int i = 0;
    // if(i++ == 0)
    //     std::cout << "Map draw called" << std::endl;
    // std::cout << lanes[0]->getY() << std::endl;
}

void Map::update() {
    for (auto lane : lanes) {
        lane->setY(lane->getY() + speed);
    }

    if (lanes.back()->getY() > 982.0f) {
        delete lanes.back();
        lanes.pop_back();
        Lane *lane = new Lane(lanes.front()->getY() - 95.0f, 0);
        lanes.push_front(lane);
        // std::cout << lanes.front()->getY() << std::endl;
    }

    for (auto lane : lanes) {
        lane->update();
    }
    // static int i = 0;
    // if(i++ == 0)
    //     std::cout << "Map update called" << std::endl;
}

void Map::setSpeed(float speed) {
    this->speed = speed;
}

Map::~Map() {
    for (auto lane : lanes) {
        delete lane;
    }
    lanes.clear();
}

bool Map::CheckCollisionPlayer(Rectangle playerBoxCollision) {
    for (auto lane : lanes) {
        if (lane->CheckCollisionPlayer(playerBoxCollision))
            return true;
    }
    return false;
}