#include "save.h"
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

saveData::saveData() : seed(0), highScore(0), score(0), position({ 0, 0 }), targetPosition({ 0, 0 }), vSpeed(0), hSpeed(0), frameCount(0), skinID(0) {
}

saveData::saveData(GameState* gameState) {
    this->serialized_data = gameState->serializeData();
    // load(this->serialized_data);
}

saveData::saveData(std::string serialized_data) {
    this->serialized_data = serialized_data;
    // load(this->serialized_data);
}

void saveData::setSeed(unsigned long long seed) {
    this->seed = seed;
}

void saveData::setHighScore(int highScore) {
    this->highScore = highScore;
}

void saveData::setScore(int score) {
    this->score = score;
}

void saveData::setPosition(std::pair<float, float> position) {
    this->position = position;
}

void saveData::setTargetPosition(std::pair<float, float> targetPosition) {
    this->targetPosition = targetPosition;
}

void saveData::setVSpeed(float vSpeed) {
    this->vSpeed = vSpeed;
}

void saveData::setHSpeed(float hSpeed) {
    this->hSpeed = hSpeed;
}

void saveData::setFrameCount(int frameCount) {
    this->frameCount = frameCount;
}

void saveData::setSkinID(int skinID) {
    this->skinID = skinID;
}

void saveData::serialize() {
    this->serialized_data = "";
    this->serialized_data += std::to_string(seed) + "\n";
    this->serialized_data += std::to_string(highScore) + "\n";
    this->serialized_data += std::to_string(score) + "\n";
    this->serialized_data += std::to_string(position.first) + "\n";
    this->serialized_data += std::to_string(position.second) + "\n";
    this->serialized_data += std::to_string(targetPosition.first) + "\n";
    this->serialized_data += std::to_string(targetPosition.second) + "\n";
    this->serialized_data += std::to_string(vSpeed) + "\n";
    this->serialized_data += std::to_string(hSpeed) + "\n";
    this->serialized_data += std::to_string(frameCount) + "\n";
    this->serialized_data += std::to_string(skinID) + "\n";
}

void saveData::save(int slot) {
    std::string filename = "save" + std::to_string(slot) + ".dat";
    std::ofstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file " + filename);
    }

    file.write(this->serialized_data.c_str(), this->serialized_data.size());
    file.close();
}

void saveData::load(int slot) {
    std::string filename = "save" + std::to_string(slot) + ".dat";
    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file " + filename);
    }

    std::string serialized_data;
    std::string line;

    while (std::getline(file, line)) {
        serialized_data += line + "\n";
    }

    file.close();

    // load(serialized_data);
}


void saveData::load(std::string serialized_data) {
    std::string line;
    std::stringstream ss(serialized_data);

    std::getline(ss, line);
    this->seed = std::stoull(line);

    std::getline(ss, line);
    this->highScore = std::stoi(line);

    std::getline(ss, line);
    this->score = std::stoi(line);

    std::getline(ss, line);
    this->position.first = std::stof(line);

    std::getline(ss, line);
    this->position.second = std::stof(line);

    std::getline(ss, line);
    this->targetPosition.first = std::stof(line);

    std::getline(ss, line);
    this->targetPosition.second = std::stof(line);

    std::getline(ss, line);
    this->vSpeed = std::stof(line);

    std::getline(ss, line);
    this->hSpeed = std::stof(line);

    std::getline(ss, line);
    this->frameCount = std::stoi(line);

    std::getline(ss, line);
    this->skinID = std::stoi(line);
}
