#include "Obstacle.h" 
#include"GameSettings.h"

Obstacle::Obstacle(const Vector2& pos, float spd) : position(pos), speed(spd) {}
// Destructor
Obstacle::~Obstacle() {
    // Cleanup code here
}

float Obstacle::getSpeed() const{
    return speed;
}

Vector2 Obstacle::getPos(){
    return position;
}

void Obstacle::setPos(float x, float y){
    position.x = x;
    position.y = y;
}

bool Obstacle::checkOutOfScreen() const{
    if (position.x < 0 || position.x > settings::SCREEN_WIDTH) return true;
    return false;
}