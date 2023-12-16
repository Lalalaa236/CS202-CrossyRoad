#include "Obstacle.h"
#include "GameSettings.h"

Obstacle::Obstacle(const Vector2 &pos, float spd) : position(pos), speed(spd) {
}

// Copy constructor
Obstacle::Obstacle(const Obstacle &obstacle) {
    position = obstacle.position;
    speed = obstacle.speed;
}

// Destructor
Obstacle::~Obstacle() {
    // Cleanup code here
}

// Assignment operator
Obstacle &Obstacle::operator=(const Obstacle &obstacle) {
    if (this == &obstacle)
        return *this;

    position = obstacle.position;
    speed = obstacle.speed;

    return *this;
}

float Obstacle::getSpeed() const {
    return speed;
}

Vector2 Obstacle::getPos() {
    return position;
}

void Obstacle::setPos(float x, float y) {
    position.x = x;
    position.y = y;
}

bool Obstacle::checkOutOfScreen() const {
    if (position.x < 0 - size.first || position.x > settings::SCREEN_WIDTH + size.first)
        return true;
    return false;
}

void Obstacle::setBoxCollision(float x, float y) {
    boxCollision.x = x;
    boxCollision.y = y;
    boxCollision.width = size.first - size.first * settings::BOXCOLLISION_SCALE;
    boxCollision.height = size.second - size.second * settings::BOXCOLLISION_SCALE;
}

Rectangle Obstacle::getBoxCollision() const {
    return boxCollision;
}

void Obstacle::setSpeed(float speed) {
    this->speed = speed;
}

unsigned Obstacle::getUSpeed() const {
    return *(unsigned *)&speed;
}

void Obstacle::resetPos() {
    if (!(getUSpeed() & 0x80000000))
        position.x = -size.first;
    else
        position.x = settings::SCREEN_WIDTH + size.first;
}