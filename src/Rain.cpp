#include "rain.h"
#include <algorithm>

Rain::Rain()
{
    raindropShape.width = 4;
    raindropShape.height = 20;
    state = false;
}

void Rain::setState(bool st)
{
    state = st;
}

bool Rain::getState()
{
    return state;
}

void Rain::update(int screenWidth, int screenHeight)
{
    for (int i = 0; i < 20; ++i)
    {
        if (GetRandomValue(0, 200) < 10)
        {
            float x = static_cast<float>(GetRandomValue(0, screenWidth + 200));
            Color randomColor = BLUE;
            raindrops.push_back({Vector2{x, 0}, randomColor, static_cast<float>(GetRandomValue(-45, 45))});
        }
    }
}

void Rain::drawTo()
{
    for (auto& raindrop : raindrops)
    {
        raindrop.position.x -= 4;
        raindrop.position.y += 10;

        DrawRectanglePro({raindrop.position.x, raindrop.position.y, raindropShape.width, raindropShape.height}, 
                         Vector2{raindropShape.width / 2, raindropShape.height / 2}, 
                         raindrop.rotation, 
                         raindrop.color);
    }

    raindrops.erase(
        std::remove_if(
            raindrops.begin(),
            raindrops.end(),
            [screenHeight = GetScreenHeight()](const Raindrop& rd) {
                return rd.position.y > screenHeight;
            }),
        raindrops.end());
}
