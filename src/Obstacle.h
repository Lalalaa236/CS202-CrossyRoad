#pragma once

class Obstacle {
public:
    virtual void move(float x, float y);
    virtual void makeSound();
    virtual bool checkType();
    virtual ~Obstacle();
    virtual bool CheckOutOfScreen();
private:
    float speed;
    float x, y;
};