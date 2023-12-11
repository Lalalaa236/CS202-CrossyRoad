// Tiger.cpp
#include "Tiger.h"
#include "../GameSettings.h"
#include "../TextureHolder.h"
#include <iostream>

Tiger::Tiger(const Vector2& pos, float speed) : Obstacle(pos, speed), numsFrame(6), curFrame(0), frameTime(0.0f) {
    // Load Tiger frames
    for (int i = 0; i < numsFrame; i++) {
        txt.push_back(&TextureHolder::getHolder().get((Textures::ID)(Textures::TIGER_1 + i)));
    }
}

Tiger::~Tiger() {
    txt.clear();
}

void Tiger::update(float k) {
    this->setPos(this->getPos().x, k);

    frameTime += GetFrameTime();
    if (frameTime >= 0.1f) { // Change this value to control the frame rate
        frameTime = 0.0f;
        curFrame = (curFrame + 1) % numsFrame;
    }

    Vector2 tmp = this->getPos();

    // Move horizontally based on some speed (adjust as needed)
    tmp.x += this->getSpeed() * frameTime * 10;
    setPos(tmp.x, tmp.y);

    // If the obstacle is out of screen, move it to the other side
    float width = txt[curFrame]->width * 0.5f;
    if (checkOutOfScreen(width)) {
        if (this->getSpeed() > 0)
            setPos(-width, tmp.y);
        else
            setPos(settings::SCREEN_WIDTH + width, tmp.y);
    }
}


void Tiger::draw() {
    float scale = 0.5f;
    Vector2 tmp = this->getPos();

    Rectangle srcRect = { 0.0f, 0.0f, (float)txt[curFrame]->width, (float)txt[curFrame]->height };
    Rectangle destRect = { tmp.x, tmp.y, (float)txt[curFrame]->width * scale, (float)txt[curFrame]->height * scale };

    // Flip the sprite based on the direction
    if (this->getSpeed() < 0)
        srcRect.width = -srcRect.width;

    DrawTexturePro(*txt[curFrame], srcRect, destRect, { 0, 0 }, 0.0f, WHITE);

    setBoxCollision(this->getPos().x, this->getPos().y, txt[curFrame], scale);
}
