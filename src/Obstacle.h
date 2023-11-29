#pragma once
#include"raylib.h"

class Obstacle {
public:
    Obstacle(const Vector2& pos, float speed);
    virtual ~Obstacle();
    virtual void draw() = 0;
    float getSpeed() const;
    Vector2 getPos();
    void setPos(float x, float y);
    virtual void update(float y) = 0;
    bool checkOutOfScreen() const;
    Rectangle getBoxCollision() const;
private:
    float speed;
    Vector2 position;
protected:
    Rectangle boxCollision;
    void setBoxCollision(float x, float y, Texture2D* txt, float scale);
};