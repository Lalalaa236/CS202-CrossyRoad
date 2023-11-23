#include "Player.h"

Player::Player(float x, float y)
: position({x, y}), isAlive(true)
{}

Player::Player(float x, float y, bool isAlive)
: position({x, y}), isAlive(isAlive)
{}

void Player::up()
{
    position.second -= settings::GRID_SIZE.second;
}

void Player::down()
{
    position.second += settings::GRID_SIZE.second;
}

void Player::left()
{
    position.first -= settings::GRID_SIZE.first;
}

void Player::right()
{
    position.first += settings::GRID_SIZE.first;
}

std::pair<float, float> Player::getPosition()
{
    return position;
}

void Player::move(Direction direction)
{
    switch(direction)
    {
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

bool Player::getIsAlive()
{
    return isAlive;
}