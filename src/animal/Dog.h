#pragma once
#include "../Obstacle.h"
#include "raylib.h"
#include <string>
#include <vector>

class Dog : public Obstacle {
private:
    std::vector<Texture2D *> txt; // Vector of Texture2D (frames)

    int numsFrame, curFrame; // Store frames to draw
    float frameTime;

public:
    //Constructor
    Dog(const Vector2 &pos, float Speed);
    ~Dog();
    void draw() override;
    void update(float y) override;
};