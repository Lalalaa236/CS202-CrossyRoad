#pragma once
#include"raylib.h"
#include <string>
#include <vector>
#include"Obstacle.h"


class Bike : public Obstacle{
private:
    std::vector<Texture2D *> txt;  // Vector of Texture2D (frames)

    int numsFrame, curFrame;       // Store frames to draw
    float frameTime;
public:
    //Constructor
    Bike(const Vector2& pos,float Speed);
    ~Bike();        
    void draw() override;
    void update(float y) override;
};


