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
    int state;
    Sound rainSound;
    bool isToggleSound;

public:
    Rain();
    void setState(int st);
    int getState();
    void update(int screenWidth, int screenHeight);
    void drawTo();
    ~Rain();
};
