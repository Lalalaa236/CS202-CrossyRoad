#include "Map.h"
#include <iostream>
#include <sstream>

Map::Map(float speed) : speed(speed) {
    // Initialize first j lane to be safe
    int j = rand() % 1 + 3;
    int i = 0;

    for (; i < 12 - j; ++i) {
        Lane* lane = new Lane(-158.0f + i * 95.0f, speed);
        lanes.push_back(lane);
    }

    for (int k = 1; k <= j; ++k, ++i) {
        Lane* lane = new Lane(-158.0f + i * 95.0f, speed, Lane::LaneType::GRASS, 0);
        lanes.push_back(lane);
    }
}

void Map::draw() {
    for (auto lane : lanes)
        lane->draw();
}

void Map::update(int score) {
    for (auto lane : lanes) {
        lane->setY(lane->getY() + speed);
    }

    if (lanes.back()->getY() > 982.0f) {
        delete lanes.back();
        lanes.pop_back();
        Lane* lane = new Lane(lanes.front()->getY() - 95.0f, 0, score);
        lanes.push_front(lane);
    }

    for (auto lane : lanes) {
        lane->update();
    }
}

void Map::setSpeed(float speed) {
    this->speed = speed;
}

Map::~Map() {
    for (auto lane : lanes)
        delete lane;
    lanes.clear();
}

bool Map::CheckCollisionPlayer(Rectangle playerBoxCollision) {
    for (auto lane : lanes) {
        if (lane->CheckCollisionPlayer(playerBoxCollision))
            return true;
    }
    return false;
}

// [mapData] = [speed] [n] [laneData1] [laneData2] ... [laneDataN]
std::string Map::serializeData() {
    std::string serialized_data = "";

    serialized_data += std::to_string(speed) + " ";
    serialized_data += std::to_string(lanes.size()) + "\n";

    for (auto lane : lanes)
        serialized_data += lane->serializeData() + "\n";

    return serialized_data;
}

void Map::loadSerializedData(std::string serialized_data) {
    std::istringstream iss(serialized_data);
    int n;

    iss >> speed >> n;

    for (int i = 0; i < n; ++i) {
        std::string laneData = "";
        std::getline(iss, laneData, '\n');

        Lane* lane = new Lane(0, 0);
        lane->loadSerializedData(laneData);
        lanes.push_back(lane);
    }
}
