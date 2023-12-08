#pragma once

#include <raylib.h>
#include <vector>

class Rain
{
private:
    struct Raindrop
    {
        Vector2 position;
        Color color;
        float rotation;
    };

    std::vector<Raindrop> raindrops;
    Rectangle raindropShape;
    bool state;

public:
    Rain();
    void setState(bool st);
    bool getState();
    void update(int screenWidth, int screenHeight);
    void drawTo();
};
