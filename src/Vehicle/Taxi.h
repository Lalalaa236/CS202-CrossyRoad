#pragma once
#include "../Obstacle.h"
#include "raylib.h"
#include <string>
#include <vector>

class Taxi: public Obstacle {
private:
    std::vector<Texture2D *> txt; // Vector of Texture2D (frames)

    int numsFrame, curFrame; // Store frames to draw
    float frameTime;

public:
    //Constructor
    Taxi(const Vector2 &pos, float Speed);
    ~Taxi();
    void draw() override;
    void update(float y) override;
};