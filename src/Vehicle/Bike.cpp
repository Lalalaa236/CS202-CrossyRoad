// Bike.cpp
#include "Bike.h"
#include "../GameSettings.h"
#include "../TextureHolder.h"
#include <iostream>

Bike::Bike(const Vector2& pos, float speed) : Obstacle(pos, speed), numsFrame(10), curFrame(0), frameTime(0.0f) {
    // Load Bike frames
    for (int i = 0; i < numsFrame; i++) {
        txt.push_back(&TextureHolder::getHolder().get((Textures::ID)(Textures::BIKE_1 + i)));
    }
}

Bike::~Bike() {
}

void Bike::update(float k) {
    this->setPos(this->getPos().x, k - 35);

    frameTime += GetFrameTime();
    if (frameTime >= 0.1f) { // Change this value to control the frame rate
        frameTime = 0.0f;
        curFrame = (curFrame + 1) % numsFrame;
    }

    Vector2 tmp = this->getPos();

    // Move horizontally based on some speed (adjust as needed)
    tmp.x += this->getSpeed() * frameTime * 10;
    setPos(tmp.x, tmp.y);

    if (checkOutOfScreen(50)) {
        if (this->getSpeed() > 0)
            setPos(-50, tmp.y);
        else
            setPos(settings::SCREEN_WIDTH + 50, tmp.y);
    }
}


void Bike::draw() {
    float scale = 0.35f;
    Vector2 tmp = this->getPos();

    Rectangle srcRect = { 0.0f, 0.0f, (float)txt[curFrame]->width, (float)txt[curFrame]->height };
    Rectangle destRect = { tmp.x, tmp.y, (float)txt[curFrame]->width * scale, (float)txt[curFrame]->height * scale };

    // Flip the sprite based on the direction
    if (this->getSpeed() < 0)
        srcRect.width = -srcRect.width;

    DrawTexturePro(*txt[curFrame], srcRect, destRect, { 0, 0 }, 0.0f, WHITE);

    setBoxCollision(this->getPos().x, this->getPos().y, txt[curFrame], scale);

    // For debugging
    // DrawRectangleLines(boxCollision.x, boxCollision.y, boxCollision.width, boxCollision.height, RED);
}
