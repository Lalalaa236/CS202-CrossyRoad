#pragma once
#include "GameSettings.h"
#include "Obstacle.h"
#include "TextureHolder.h"
#include "raylib.h"
#include <iostream>
#include <string>
#include <vector>

class Tiger : public Obstacle {
private:
    std::vector<Texture2D *> txt; // Vector of Texture2D (frames)

    int numsFrame, curFrame; // Store frames to draw
    float frameTime;

public:
    //Constructor
    Tiger(const Vector2 &pos, float Speed);
    ~Tiger();
    void draw() override;
    void update(float y) override;
};