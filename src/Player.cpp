#include "Player.h"

Player::Player(float x, float y, float mapSpeed)
    : position({x, y}), targetPosition({x, y}), isAlive(true), mapSpeed(mapSpeed), vSpeed(0.0f),
      hSpeed(0.0f) {
    boxCollision.x = x;
    boxCollision.y = y;
    boxCollision.width = 82;
    boxCollision.height = 82;
}

Player::Player(float x, float y, bool isAlive)
    : position({x, y}), targetPosition({x, y}), isAlive(isAlive), vSpeed(0.0f), hSpeed(0.0f) {
}

void Player::up() {
    targetPosition.second -= settings::GRID_SIZE.second;
    vSpeed = -10.0f;
    // position.second -= settings::GRID_SIZE.second;
    // boxCollision.y -= settings::GRID_SIZE.second;
}

void Player::down() {
    targetPosition.second += settings::GRID_SIZE.second;
    vSpeed = 10.0f;
    // position.second += settings::GRID_SIZE.second;
    // boxCollision.y += settings::GRID_SIZE.second;
}

void Player::left() {
    targetPosition.first -= settings::GRID_SIZE.first;
    hSpeed = -10.0f;
    // position.first -= settings::GRID_SIZE.first;
    // boxCollision.x -= settings::GRID_SIZE.first;
}

void Player::right() {
    targetPosition.first += settings::GRID_SIZE.first;
    hSpeed = 10.0f;
    // position.first += settings::GRID_SIZE.first;
    // boxCollision.x += settings::GRID_SIZE.first;
}

std::pair<float, float> Player::getPosition() const {
    return position;
}

void Player::move(Direction direction) {
    switch (direction) {
    case Direction::UP:
        up();
        break;
    case Direction::DOWN:
        down();
        break;
    case Direction::LEFT:
        left();
        break;
    case Direction::RIGHT:
        right();
        break;
    }
}

bool Player::getIsAlive() const {
    return isAlive;
}

void Player::setIsAlive(bool isAlive) {
    this->isAlive = isAlive;
}

Rectangle Player::getBoxCollision() const {
    return boxCollision;
}

void Player::update() {
    targetPosition.second += mapSpeed;

    position.second += mapSpeed;
    boxCollision.y += mapSpeed;

    if (targetPosition.first < 0 || targetPosition.first > 1512 - 82)
        return;

    if ((position.first + hSpeed > targetPosition.first) && hSpeed < 0.0f) {
        position.first += hSpeed;
        boxCollision.x += hSpeed;
    } else if ((position.first + hSpeed < targetPosition.first) && hSpeed > 0.0f) {
        position.first += hSpeed;
        boxCollision.x += hSpeed;
    } else {
        position.first = targetPosition.first;
        boxCollision.x = targetPosition.first;
        hSpeed = 0.0f;
    }

    if ((position.second + vSpeed > targetPosition.second) && vSpeed < 0.0f) {
        position.second += vSpeed;
        boxCollision.y += vSpeed;
    } else if ((position.second + vSpeed < targetPosition.second) && vSpeed > 0.0f) {
        position.second += vSpeed;
        boxCollision.y += vSpeed;
    } else {
        position.second = targetPosition.second;
        boxCollision.y = targetPosition.second;
        vSpeed = 0.0f;
    }
}

void Player::setMapSpeed(float mapSpeed) {
    this->mapSpeed = mapSpeed;
}

void Player::draw() {
    DrawRectangleRec(boxCollision, RED);
}

// void Player::setTargetPosition(std::pair<float, float> targetPosition)
// {
//     this->targetPosition = targetPosition;
// }

// std::pair<float, float> Player::getTargetPosition() const
// {
//     return targetPosition;
// }

// void Player::setVSpeed(float vSpeed)
// {
//     this->vSpeed = vSpeed;
// }

// void Player::setHSpeed(float hSpeed)
// {
//     this->hSpeed = hSpeed;
// }