// Train.cpp
#include "Train.h"


Train::Train(const Vector2& pos, float speed) : Obstacle(pos, speed), numsFrame(1), curFrame(0), frameTime(0.0f) {
    // Load Train frames
    txt.push_back(&TextureHolder::getHolder().get((Textures::ID)(Textures::TRAIN_RIGHT)));
    scale = 0.7f;
    size.first = settings::TRAIN_SIZE.first * scale;
    size.second = settings::TRAIN_SIZE.second * scale;
    setBoxCollision();
    sound = LoadSound("image/Sound/train.mp3");
    //PlaySound(sound);
}

Train::~Train() {
    txt.clear();
    UnloadSound(sound);
}

void Train::update(float k) {
    if (checkOutOfScreen())
        resetPos();
    position.y = k;
    static float elapsedTime = 0.0f;
    
    // Change this value to control the interval between sounds
    const float soundInterval = 7.0f;

    // Update the elapsed time
    elapsedTime += GetFrameTime();

    if (elapsedTime >= soundInterval) {
        // Play the sound
        PlaySound(sound);

        // Reset the elapsed time
        elapsedTime = 0.0f;
    }
    if (frameTime >= 0.1f) { // Change this value to control the frame rate
        frameTime = 0.0f;
        curFrame = (curFrame + 1) % numsFrame;
    }

    // Move horizontally based on some speed (adjust as needed)

    position.x += speed * frameTime * 100;
    // If the obstacle is out of screen, move it to the other side
    frameTime += GetFrameTime();
}


void Train::draw() {
    Rectangle srcRect = { 0.0f, 0.0f, (float)txt[curFrame]->width, (float)txt[curFrame]->height };
    Rectangle destRect = { position.x, position.y, (float)txt[curFrame]->width * scale, (float)txt[curFrame]->height * scale };

    // Flip the sprite based on the direction
    if (!(this->getUSpeed() & 0x80000000))
        srcRect.width = -srcRect.width;

    DrawTexturePro(*txt[curFrame], srcRect, destRect, { 0, 0 }, 0.0f, WHITE);

    setBoxCollision();

    // For debugging
    DrawRectangleLines(boxCollision.x, boxCollision.y, boxCollision.width, boxCollision.height, RED);
}