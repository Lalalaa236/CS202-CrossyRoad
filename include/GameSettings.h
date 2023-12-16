#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

#define SEMI_TRANSPARENT                                                                                               \
    CLITERAL(Color) {                                                                                                  \
        0, 0, 0, 120                                                                                                   \
    }

#include "raylib.h"

#include <string>
#include <utility>

namespace settings {
    constexpr int SCREEN_WIDTH = 1512;
    constexpr int SCREEN_HEIGHT = 982;
    constexpr int SCREEN_FPS = 60;
    constexpr float BOXCOLLISION_SCALE = 0.9f;
    constexpr std::pair<float, float> GRID_SIZE = { 89.375f, 95.0f }; // 17 wide, 11 tall
    constexpr std::pair<float, float> PLAYER_SIZE = { 82.0f, 82.0f };
    constexpr std::pair<float, float> BIKE_SIZE = { 314.0f, 284.0f };
    constexpr std::pair<float, float> BIRD_SIZE = { 762.0f, 620.0f };
    constexpr std::pair<float, float> CAB_SIZE = { 520.0f, 235.0f };
    constexpr std::pair<float, float> CAR_SIZE = { 246.0f, 78.0f };
    constexpr std::pair<float, float> CAT_SIZE = { 498.0f, 292.0f };
    constexpr std::pair<float, float> DOG_SIZE = { 300.0f, 203.0f };
    constexpr std::pair<float, float> RABBIT_SIZE = { 219.0f, 87.0f };
    constexpr std::pair<float, float> TAXI_SIZE = { 540.0f, 149.0f };
    constexpr std::pair<float, float> TIGER_SIZE = { 223.0f, 104.0f };
    constexpr std::pair<float, float> TRAIN_SIZE = { 1497.0f, 96.0f };
    constexpr std::pair<float, float> TRUCK_SIZE = { 495.0f, 194.0f };

    extern int CURRENT_SKIN;
} // namespace settings

namespace data {
    extern std::string Game;
    extern std::string Map;
    extern std::string Player;
} // namespace data

#endif