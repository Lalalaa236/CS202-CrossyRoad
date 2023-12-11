#pragma once
#include "../Obstacle.h"
#include "raylib.h"
#include <string>
#include <vector>

class Train : public Obstacle {
private:
    std::vector<Texture2D *> txt; // Vector of Texture2D (frames)

    int numsFrame, curFrame; // Store frames to draw
    float frameTime;

public:
    //Constructor
    Train(const Vector2 &pos, float Speed);
    ~Train();
    void draw() override;
    void update(float y) override;
};