// Bird.cpp
#include "../../include/Bird.h"

Bird::Bird(const Vector2 &pos, float speed) : Obstacle(pos, speed), numsFrame(8), curFrame(0), frameTime(0.0f) {
    // Load bird frames
    for (int i = 0; i < numsFrame; i++) {
        txt.push_back(&TextureHolder::getHolder().get((Textures::ID)(Textures::BIRD_1 + i)));
    }
    scale = 0.1f;
    size.first = settings::BIRD_SIZE.first * scale;
    size.second = settings::BIRD_SIZE.second * scale;
    setBoxCollision();
}

Bird::~Bird() {
    txt.clear();
}

void Bird::update(float k) {
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


void Bird::draw() {
    Rectangle srcRect = {0.0f, 0.0f, (float)txt[curFrame]->width, (float)txt[curFrame]->height};
    Rectangle destRect = {position.x, position.y, (float)txt[curFrame]->width * scale, (float)txt[curFrame]->height * scale};

    // Flip the sprite based on the direction
    if (this->getSpeed() < 0)
        srcRect.width = -srcRect.width;

    DrawTexturePro(*txt[curFrame], srcRect, destRect, {0, 0}, 0.0f, WHITE);

    setBoxCollision();

    // For debugging
    //DrawRectangleLines(boxCollision.x, boxCollision.y, boxCollision.width, boxCollision.height, RED);
}
