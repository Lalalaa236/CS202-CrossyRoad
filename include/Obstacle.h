#pragma once
#include "raylib.h"
#include <utility>

class Obstacle {
public:
    Obstacle(const Vector2& pos, float speed);
    Obstacle(const Obstacle& obstacle);
    virtual ~Obstacle();

    Obstacle& operator=(const Obstacle& obstacle);

    Vector2 getPos();
    float getSpeed() const;
    void setPos(float x, float y);
    void setSpeed(float speed);
    bool checkOutOfScreen() const;
    Rectangle getBoxCollision() const;
    unsigned getUSpeed() const;

    virtual void draw() = 0;
    virtual void update(float y) = 0;
    void resetPos();

protected:
    Vector2 position;
    float speed;
    float scale;
    std::pair<float, float> size = {0, 0};
    Rectangle boxCollision;
    void setBoxCollision(float x, float y);
};