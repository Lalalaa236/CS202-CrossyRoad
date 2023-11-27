#pragma once
#include"raylib.h"

class Obstacle {
public:
    Obstacle(const Vector2& pos, float speed);
    virtual ~Obstacle();

    Vector2 getPos();
    float getSpeed() const;
    void setPos(float x, float y);

    bool checkOutOfScreen() const;

    virtual void draw() = 0;
    virtual void update(float y) = 0;

private:
    float speed;
    Vector2 position;
};