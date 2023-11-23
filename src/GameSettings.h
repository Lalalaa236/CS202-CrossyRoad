#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

#include <utility>

namespace settings
{
    constexpr int SCREEN_WIDTH = 1512;
    constexpr int SCREEN_HEIGHT = 982;
    constexpr int SCREEN_FPS = 60;
    constexpr std::pair<float, float> GRID_SIZE = { 1512, 98.2 }; // 8 wide, 10 tall
}

#endif