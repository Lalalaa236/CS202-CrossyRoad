#pragma once

#include <raylib.h>
#include <vector>

class SpecialEffect
{
protected:
    struct Particle
    {
        Vector2 position;
        Color color;
        float rotation;
    };

    std::vector<Particle> particles;
    Rectangle particleShape;
    int state;
    Sound effectSound;
    bool isToggleSound;

public:
    SpecialEffect();
    virtual ~SpecialEffect() = default;

    void setState(int st);
    int getState();
    virtual void update(int screenWidth, int screenHeight) = 0;
    virtual void drawTo() = 0;
};
