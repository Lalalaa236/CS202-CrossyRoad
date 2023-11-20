#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

#include <utility>

namespace settings
{
    constexpr int SCREEN_WIDTH = 1200;
    constexpr int SCREEN_HEIGHT = 800;
    constexpr int SCREEN_FPS = 60;
    constexpr std::pair<float, float> GRID_SIZE = { 150, 100 }; // 8 wide, 8 tall
}

#endif