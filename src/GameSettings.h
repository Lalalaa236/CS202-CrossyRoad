#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

#define SEMI_TRANSPARENT CLITERAL(Color) { 0, 0, 0, 120 }

#include <utility>

namespace settings
{
    constexpr int SCREEN_WIDTH = 1512;
    constexpr int SCREEN_HEIGHT = 982;
    constexpr int SCREEN_FPS = 60;
    constexpr std::pair<float, float> GRID_SIZE = { 89.375f, 95.0f }; // 17 wide, 11 tall
    constexpr std::pair<float, float> PLAYER_SIZE = { 82.0f, 82.0f };
}

#endif