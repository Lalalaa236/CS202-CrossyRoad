#ifndef SAVE_H
#define SAVE_H

#include "gameState.h"
#include "Player.h"
#include "raylib.h"
#include <algorithm>
#include <utility>

class saveData {
private:
    // Game information
    unsigned long long seed;
    int highScore;
    int score;

    // Player information
    std::pair<float, float> position;
    std::pair<float, float> targetPosition;
    float vSpeed, hSpeed;
    int frameCount;

    int skinID;

    // Data
    std::string serialized_data;

public:
    saveData();
    saveData(GameState* gameState);
    saveData(std::string serialized_data);

    // Setter
    void setSeed(unsigned long long seed);
    void setHighScore(int highScore);
    void setScore(int score);
    void setPosition(std::pair<float, float> position);
    void setTargetPosition(std::pair<float, float> targetPosition);
    void setVSpeed(float vSpeed);
    void setHSpeed(float hSpeed);
    void setFrameCount(int frameCount);
    void setSkinID(int skinID);

    // Method
    void serialize();
    void save(int slot = 0);
    void load(int slot = 0);
    void load(std::string serialized_data);
};

#endif // SAVE_H