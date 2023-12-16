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

bool Obstacle::checkOutOfScreen(float error) const {
    if (position.x < 0 - error || position.x > settings::SCREEN_WIDTH + error)
        return true;
    return false;
}

void Obstacle::setBoxCollision(float x, float y, Texture2D *txt, float scale) {
    boxCollision.x = x;
    boxCollision.y = y;
    boxCollision.width = txt->width * scale;
    boxCollision.height = txt->height * scale;
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