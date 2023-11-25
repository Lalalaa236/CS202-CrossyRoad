#include "Player.h"

Player::Player(float x, float y, float mapSpeed)
: position({x, y}), isAlive(true), mapSpeed(mapSpeed)
{
    boxCollision.x = x;
    boxCollision.y = y;
    boxCollision.width = settings::GRID_SIZE.first;
    boxCollision.height = settings::GRID_SIZE.second;
}

Player::Player(float x, float y, bool isAlive)
: position({x, y}), isAlive(isAlive)
{}

void Player::up()
{
    position.second -= settings::GRID_SIZE.second;
    boxCollision.y -= settings::GRID_SIZE.second;
}

void Player::down()
{
    position.second += settings::GRID_SIZE.second;
    boxCollision.y += settings::GRID_SIZE.second;
}

void Player::left()
{
    position.first -= settings::GRID_SIZE.first;
    boxCollision.x -= settings::GRID_SIZE.first;
}

void Player::right()
{
    position.first += settings::GRID_SIZE.first;
    boxCollision.x += settings::GRID_SIZE.first;
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

void Player::setIsAlive(bool isAlive)
{
    this->isAlive = isAlive;
}

Rectangle Player::getBoxCollision()
{
    return boxCollision;
}

void Player::update()
{
    position.second += mapSpeed;
    boxCollision.y += mapSpeed;
}

void Player::setMapSpeed(float mapSpeed)
{
    this->mapSpeed = mapSpeed;
}

void Player::draw()
{
    DrawRectanglePro(boxCollision, {position.first, position.second}, 0, RED);
}