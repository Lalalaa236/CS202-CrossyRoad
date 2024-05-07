// Truck.cpp
#include "../../include/Truck.h"

Truck::Truck(const Vector2 &pos, float speed) : Obstacle(pos, speed), numsFrame(5), curFrame(0), frameTime(0.0f) {
    // Load Truck frames
    for (int i = 0; i < numsFrame; i++) {
        txt.push_back(&TextureHolder::getHolder().get((Textures::ID)(Textures::TRUCK_1 + i)));
    }
    scale = 0.38f;
    size.first = settings::TRUCK_SIZE.first * scale;
    size.second = settings::TRUCK_SIZE.second * scale;
    setBoxCollision();
}

Truck::~Truck() {
    txt.clear();
}

void Truck::update(float k) {
    position.y = k;

    if (frameTime >= 0.1f) { // Change this value to control the frame rate
        frameTime = 0.0f;
        curFrame = (curFrame + 1) % numsFrame;
    }

    // Move horizontally based on some speed (adjust as needed)
    position.x += speed * frameTime * 10;

    // If the obstacle is out of screen, move it to the other side
    if (checkOutOfScreen())
        resetPos();
    
    frameTime += GetFrameTime();
}


void Truck::draw() {

    Rectangle srcRect = {0.0f, 0.0f, (float)txt[curFrame]->width, (float)txt[curFrame]->height};
    Rectangle destRect = {position.x, position.y, (float)txt[curFrame]->width * scale, (float)txt[curFrame]->height * scale};

    // Flip the sprite based on the direction
    if (this->getUSpeed() & 0x80000000)
        srcRect.width = -srcRect.width;

    DrawTexturePro(*txt[curFrame], srcRect, destRect, {0, 0}, 0.0f, WHITE);

    setBoxCollision();

    // For debugging
    //DrawRectangleLines(boxCollision.x, boxCollision.y, boxCollision.width, boxCollision.height, RED);
}
