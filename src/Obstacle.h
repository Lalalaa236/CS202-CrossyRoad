#pragma once
#include "raylib.h"

class Obstacle {
public:
    Obstacle(const Vector2& pos, float speed);
    Obstacle(const Obstacle& obstacle);
    virtual ~Obstacle();

    Obstacle& operator=(const Obstacle& obstacle);

    Vector2 getPos();
    float getSpeed() const;
    void setPos(float x, float y);
    bool checkOutOfScreen() const;
    Rectangle getBoxCollision() const;

    virtual void draw() = 0;
    virtual void update(float y) = 0;

private:
    float speed;
    Vector2 position;

protected:
    Rectangle boxCollision;
    void setBoxCollision(float x, float y, Texture2D* txt, float scale);
};