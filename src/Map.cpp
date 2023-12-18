#include "Map.h"
#include <iostream>
#include <sstream>

Map::Map(float speed) : speed(speed) {
    // Initialize first j lane to be safe
    int j = rand() % 1 + 3;
    int i = 0;

    for (; i < 13 - j; ++i) {
        Lane *lane = new Lane(-253.0f + i * 95.0f, speed);
        lanes.push_back(lane);
    }

    for (int k = 1; k <= j; ++k, ++i) {
        Lane *lane = new Lane(-253.0f + i * 95.0f, speed, Lane::LaneType::GRASS, 0, Lane::ObstacleType::None);
        lanes.push_back(lane);
    }
    hitVehicle =  LoadSound("image/Sound/vehicle.mp3");
    hitAnimal = LoadSound("image/Sound/animal.wav");
}

void Map::draw() {
    for (auto lane : lanes)
        lane->draw();
}

void Map::update(int score) {
    for (auto lane : lanes) {
        lane->setY(lane->getY() + speed);
    }

    if (lanes.back()->getY() > 1072.0f) {
        delete lanes.back();
        lanes.pop_back();
        Lane *lane = new Lane(lanes.front()->getY() - 95.0f, 0, score);
        lanes.push_front(lane);
    }

    for (auto lane : lanes) {
        lane->update();
    }
}

void Map::setSpeed(float speed) {
    this->speed = speed;
}

float Map::getSpeed() const {
    return this->speed;
}

Map::~Map() {
    for (auto lane : lanes)
        delete lane;
    lanes.clear();
    UnloadSound(hitAnimal);
    UnloadSound(hitVehicle);
}

bool Map::CheckCollisionPlayer(Rectangle playerBoxCollision) {
    for (auto lane : lanes) {
        if (lane->CheckCollisionPlayer(playerBoxCollision)){
            if (lane->getType() == Lane::LaneType::ROAD)
                PlaySound(hitVehicle);
            else PlaySound(hitAnimal);
            return true;
        }
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

void Map::loadSerializedData(const std::string &serialized_data) {
    std::istringstream iss(serialized_data);
    int numLane, laneType = 0;

    iss >> speed >> numLane;
    iss.ignore();

    lanes.clear();
    for (int i = 0; i < numLane; ++i) {
        std::string laneData = "";
        std::getline(iss, laneData, '\n');

        laneType = laneData[0] - '0';

        Lane *lane = new Lane(0, 0, static_cast<Lane::LaneType>(laneType), 0, Lane::ObstacleType::None);
        lane->loadSerializedData(laneData);
        lanes.push_back(lane);
    }
}
