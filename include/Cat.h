#pragma once
#include "GameSettings.h"
#include "Obstacle.h"
#include "TextureHolder.h"
#include "raylib.h"
#include <iostream>
#include <string>
#include <vector>

class Cat : public Obstacle {
private:
    std::vector<Texture2D *> txt; // Vector of Texture2D (frames)

    int numsFrame, curFrame; // Store frames to draw
    float frameTime;

public:
    //Constructor
    Cat(const Vector2 &pos, float Speed);
    ~Cat();
    void draw() override;
    void update(float y) override;
};