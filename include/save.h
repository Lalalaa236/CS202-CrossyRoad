#ifndef SAVE_H
#define SAVE_H

#include "gameState.h"
#include "Player.h"
#include "raylib.h"
#include <algorithm>
#include <utility>

/*
    Save Data format in text file:

    [GAME]: [gameData]
    [MAP]: [mapData]
    [PLAYER]: [playerData]

    [gameData] = [seed] [highScore] [score]
    [mapData] = [speed] [n]
    [laneData1]
    [laneData2]
    ...
    [laneDataN]
    [playerData] = [position] [targetPosition] [isAlive] [vSpeed] [hSpeed] [frameCount] [skinID]

    [laneData] = [laneType] [laneSpeed] [lane.y] [laneDirection] [numObstacle] [obstacleData1] [obstacleData2] ... [obstacleDataN]

    [obstacleData] = [obstacleType] [obstacle.x]
*/

class saveData {
private:
    // Data
    std::string serialized_data = "";

    // Splitted data
    std::string playerData = "";
    std::string mapData = "";
    std::string gameData = "";

    void resetData();
    void printData();

public:
    saveData();
    // saveData(GameState* gameState);
    saveData(std::string serialized_data);

    // Getter & Setter
    int getHighScore() const;
    std::string getSerializedData() const;
    void setSerializedData(std::string serialized_data);

    // Method
    void serialize();
    void splitData();
    void save(int slot = 0);
    void load(int slot = 0);

    // TODO: Implement these methods
    void encode(std::string& data);
    void decode(std::string& data);
};

#endif // SAVE_H