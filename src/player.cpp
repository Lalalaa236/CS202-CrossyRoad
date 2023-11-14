#include "player.h"

Player::Player() {
    x = y = 0.0;
    isAlive = true;
}

Player::Player(double x, double y) {
    this->x = x;
    this->y = y;
    isAlive = true;
}

Player::~Player() {
    // TODO: Implement if needed
}

std::pair<double, double> Player::getPosition() const {
    return std::pair<double, double>(x, y);
}