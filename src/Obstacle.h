#pragma once

class Obstacle {
public:
    virtual void move() {} = 0;
    virtual void makeSound(){} = 0;
    virtual bool checkType(); 
    virtual ~Obstacle() {}
private:
    float speed;
    float x, y;
};