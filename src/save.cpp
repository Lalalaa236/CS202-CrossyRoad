#include "save.h"

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

void saveData::resetData() {
    this->gameData = this->mapData = this->playerData = "";
}

void saveData::printData() {
    std::cerr << "serialized_data: " << this->serialized_data << "\n";
    std::cerr << "gameData: " << this->gameData << "\n";
    std::cerr << "mapData: " << this->mapData << "\n";
    std::cerr << "playerData: " << this->playerData << "\n";
}

saveData::saveData() : serialized_data(""), playerData(""), mapData(""), gameData("") {
}

saveData::saveData(std::string serialized_data) {
    this->serialized_data = serialized_data;
    this->splitData();
}

int saveData::getHighScore() const {
    try {
        return std::stoi(this->gameData.substr(this->gameData.find(" ") + 1, this->gameData.find(" ", this->gameData.find(" ") + 1)));
    }
    catch (std::exception& e) {
        return 0;
    }
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

    // [GAME] [gameData]
    this->serialized_data += "[GAME]\n" + gameData + "\n";

    // [MAP] [mapData]
    this->serialized_data += "[MAP]\n" + mapData + "\n";

    // [PLAYER] [playerData]
    this->serialized_data += "[PLAYER]\n" + playerData + "\n";
}

void saveData::splitData() {
    std::string line;
    std::stringstream ss(this->serialized_data);
    std::string* pointer = nullptr;

    this->resetData();

    while (std::getline(ss, line, '\n')) {
        if (line[0] == '[') {
            if (line.find("[GAME]") != std::string::npos)
                pointer = &this->gameData;
            else if (line.find("[MAP]") != std::string::npos)
                pointer = &this->mapData;
            else if (line.find("[PLAYER]") != std::string::npos)
                pointer = &this->playerData;
            continue;
        }

        if (pointer == nullptr) { // Invalid data
            this->serialized_data = "";
            this->resetData();
            return;
        }

        *pointer += line + "\n";
    }
}

void saveData::save(int slot) {
    this->serialize();

    std::string fileName = "save" + std::to_string(slot) + ".txt";
    std::ofstream saveFile(fileName);

    if (saveFile.is_open()) {
        saveFile << this->serialized_data;
        saveFile.close();
    }
    else {
        throw std::runtime_error("Unable to open file");
    }
}

void saveData::load(int slot) {
    std::string fileName = "save" + std::to_string(slot) + ".txt";
    std::ifstream saveFile(fileName);

    // Reset data
    this->serialized_data = "";
    this->resetData();

    if (saveFile.is_open()) {
        std::string line;
        std::stringstream ss;

        while (std::getline(saveFile, line)) {
            if (line.empty() || line[0] == '\n') continue;
            ss << line << "\n";
        }

        this->serialized_data = ss.str();
        this->splitData();
    }

    saveFile.close();
}