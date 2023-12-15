#include "save.h"

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

saveData::saveData() : serialized_data(""), playerData(""), mapData(""), gameData("") {
}

saveData::saveData(std::string serialized_data) {
    this->serialized_data = serialized_data;
    this->splitData();
}

int saveData::getHighScore() const {
    return std::stoi(this->gameData.substr(this->gameData.find(" ") + 1, this->gameData.find(" ", this->gameData.find(" ") + 1)));
}

std::string saveData::getSerializedData() const {
    return this->serialized_data;
}

void saveData::setSerializedData(std::string serialized_data) {
    this->serialized_data = serialized_data;
    this->splitData();
}

void saveData::serialize() {
    this->serialized_data = "";

    // [GAME]: [gameData]
    this->serialized_data += "[GAME]: " + gameData + "\n";

    // [MAP]: [mapData]
    this->serialized_data += "[MAP]: " + mapData + "\n";

    // [PLAYER]: [playerData]
    this->serialized_data += "[PLAYER]: " + playerData + "\n";
}

void saveData::splitData() {
    std::string line;
    std::stringstream ss(this->serialized_data);

    while (std::getline(ss, line, '\n')) {
        if (line.find("[GAME]: ") != std::string::npos) {
            gameData = line.substr(8);
        }
        else if (line.find("[MAP]: ") != std::string::npos) {
            mapData = line.substr(7);
        }
        else if (line.find("[PLAYER]: ") != std::string::npos) {
            playerData = line.substr(10);
        }
    }
}

void saveData::save(int slot) {
    this->serialize();

    std::ofstream saveFile;
    std::string fileName = "save" + std::to_string(slot) + ".txt";

    saveFile.open(fileName);

    if (saveFile.is_open()) {
        saveFile << this->serialized_data;
        saveFile.close();
    }
    else {
        throw std::runtime_error("Unable to open file");
    }
}

void saveData::load(int slot) {
    std::ifstream saveFile;
    std::string fileName = "save" + std::to_string(slot) + ".txt";

    saveFile.open(fileName);

    if (saveFile.is_open()) {
        std::string line;
        std::stringstream ss;

        while (std::getline(saveFile, line)) {
            ss << line << "\n";
        }

        this->serialized_data = ss.str();
        this->splitData();

        saveFile.close();
    }
    else {
        this->serialized_data = "";
        return;
    }
}