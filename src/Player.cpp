#include "Player.h"
#include <iostream>

Player::Player(float x, float y, float mapSpeed, Textures::ID skin)
    : position({ x, y }), targetPosition({ x, y }), isAlive(true), mapSpeed(mapSpeed), vSpeed(0.0f), hSpeed(0.0f),
    frameCount(0), elapsedTime(0.0f) {
    boxCollision.x = x;
    boxCollision.y = y;
    boxCollision.width = settings::PLAYER_SIZE.first;
    boxCollision.height = settings::PLAYER_SIZE.second;

    atlas = &TextureHolder::getHolder().get(skin);
    for (int i = 0; i < frames; ++i) {
        frame[i].x = i * 64;
        frame[i].y = 192;
        frame[i].width = 64;
        frame[i].height = 64;
    }
}

Player::Player(float x, float y, float mapSpeed, Texture2D* atlas)
    : position({ x, y }), targetPosition({ x, y }), isAlive(true), mapSpeed(mapSpeed), vSpeed(0.0f), hSpeed(0.0f),
    frameCount(0), elapsedTime(0.0f) {
    boxCollision.x = x;
    boxCollision.y = y;
    boxCollision.width = settings::PLAYER_SIZE.first;
    boxCollision.height = settings::PLAYER_SIZE.second;

    this->atlas = atlas;
    for (int i = 0; i < frames; ++i) {
        frame[i].x = i * 64;
        frame[i].y = 192;
        frame[i].width = 64;
        frame[i].height = 64;
    }
}

Player::Player(float x, float y, bool isAlive, Textures::ID skin)
    : position({ x, y }), targetPosition({ x, y }), isAlive(isAlive), vSpeed(0.0f), hSpeed(0.0f), frameCount(0),
    elapsedTime(0.0f) {
    boxCollision.x = x;
    boxCollision.y = y;
    boxCollision.width = settings::PLAYER_SIZE.first;
    boxCollision.height = settings::PLAYER_SIZE.second;

    atlas = &TextureHolder::getHolder().get(skin);
    for (int i = 0; i < frames; ++i) {
        frame[i].x = i * 64;
        frame[i].y = 192;
        frame[i].width = 64;
        frame[i].height = 64;
    }
} // still need to be changed

void Player::up() {
    targetPosition.second -= settings::GRID_SIZE.second;
    vSpeed = -5.0f;
    for (int i = 0; i < frames; ++i) {
        frame[i].y = 192;
    }
    // position.second -= settings::GRID_SIZE.second;
    // boxCollision.y -= settings::GRID_SIZE.second;
}

void Player::down() {
    targetPosition.second += settings::GRID_SIZE.second;
    vSpeed = 5.0f;
    for (int i = 0; i < frames; ++i) {
        frame[i].y = 0;
    }
    // position.second += settings::GRID_SIZE.second;
    // boxCollision.y += settings::GRID_SIZE.second;
}

void Player::left() {
    targetPosition.first -= settings::GRID_SIZE.first;
    hSpeed = -5.0f;
    for (int i = 0; i < frames; ++i) {
        frame[i].y = 64;
    }
    // position.first -= settings::GRID_SIZE.first;
    // boxCollision.x -= settings::GRID_SIZE.first;
}

void Player::right() {
    targetPosition.first += settings::GRID_SIZE.first;
    hSpeed = 5.0f;
    for (int i = 0; i < frames; ++i) {
        frame[i].y = 128;
    }
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

    formerPosition = targetPosition;
    formerPosition.first -= settings::GRID_SIZE.first * (hSpeed < 0 ? -1 : hSpeed > 0 ? +1 : 0);
    formerPosition.second -= settings::GRID_SIZE.second * (vSpeed < 0 ? -1 : vSpeed > 0 ? +1 : 0);

    if (targetPosition.first < 0 || targetPosition.first > 1512 - 82)
        return;

    if ((position.first + hSpeed > targetPosition.first) && hSpeed < 0.0f) {
        position.first += hSpeed;
        boxCollision.x += hSpeed;
    }
    else if ((position.first + hSpeed < targetPosition.first) && hSpeed > 0.0f) {
        position.first += hSpeed;
        boxCollision.x += hSpeed;
    }
    else if (hSpeed != 0.0f) {
        position.first = targetPosition.first;
        boxCollision.x = targetPosition.first;
        hSpeed = 0.0f;
    }

    if ((position.second + vSpeed > targetPosition.second) && vSpeed < 0.0f) {
        position.second += vSpeed;
        boxCollision.y += vSpeed;
    }
    else if ((position.second + vSpeed < targetPosition.second) && vSpeed > 0.0f) {
        position.second += vSpeed;
        boxCollision.y += vSpeed;
    }
    else if (vSpeed != 0.0f) {
        position.second = targetPosition.second;
        boxCollision.y = targetPosition.second;
        vSpeed = 0.0f;
    }
}

void Player::setMapSpeed(float mapSpeed) {
    this->mapSpeed = mapSpeed;
}

void Player::draw() {
    // DrawRectangleRec(boxCollision, RED);
    if (position == targetPosition || (vSpeed == 0.0f && hSpeed == 0.0f) || !isMoving) {
        DrawTexturePro(*atlas, frame[0], { boxCollision.x, boxCollision.y, 82.0f, 82.0f }, { 0, 0 }, 0, WHITE);
        DrawRectangleLinesEx(boxCollision, 1, RED);
        return;
    }

    elapsedTime += GetFrameTime();
    // std::cout << elapsedTime << std::endl;

    if (elapsedTime >= 1.0f / fps) {
        ++frameCount;
        if (frameCount >= frames)
            frameCount = 0;
        elapsedTime = 0.0f;
    }

    DrawTexturePro(*atlas, frame[frameCount], { boxCollision.x, boxCollision.y, 82.0f, 82.0f }, { 0, 0 }, 0, WHITE);
    // std::cout << boxCollision.x << " " << boxCollision.y << std::endl;
    DrawRectangleLinesEx(boxCollision, 1, RED);
}

// void Player::setTargetPosition(std::pair<float, float> targetPosition)
// {
//     this->targetPosition = targetPosition;
// }

std::pair<float, float> Player::getTargetPosition() const {
    return targetPosition;
}

void Player::setSpeed(float vSpeed, float hSpeed) {
    this->vSpeed = vSpeed;
    this->hSpeed = hSpeed;
}

void Player::setSkin(Textures::ID skin) {
    atlas = &TextureHolder::getHolder().get(skin);
}

void Player::setMoving(bool isMoving) {
    this->isMoving = isMoving;
}

bool Player::getMoving() const {
    return isMoving;
}

// [playerData] = [position] [targetPosition] [isAlive] [vSpeed] [hSpeed] [frameCount] [skinID]
std::string Player::serializeData() {
    std::string serialized_data = "";

    serialized_data += std::to_string(formerPosition.first) + " " + std::to_string(formerPosition.second) + " ";
    serialized_data += std::to_string(settings::CURRENT_SKIN) + " ";

    return serialized_data;
}

void Player::loadSerializedData(std::string serialized_data) {
    std::stringstream ss(serialized_data);

    ss >> position.first >> position.second;
    ss >> settings::CURRENT_SKIN;

    hSpeed = vSpeed = 0.0f;

    // Set player skin
    TextureHolder::getHolder().load(Textures::SKIN_FULL,
        "image/skin/" + std::to_string(settings::CURRENT_SKIN) + "/full.png");

    targetPosition = position;
    boxCollision.x = position.first;
    boxCollision.y = position.second;
    boxCollision.width = settings::PLAYER_SIZE.first;
    boxCollision.height = settings::PLAYER_SIZE.second;

    atlas = &TextureHolder::getHolder().get(Textures::SKIN_FULL);
    for (int i = 0; i < frames; ++i) {
        frame[i].x = i * 64;
        frame[i].y = 192;
        frame[i].width = 64;
        frame[i].height = 64;
    }
}
