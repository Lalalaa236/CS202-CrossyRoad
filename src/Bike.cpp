// Bike.cpp
#include "Bike.h"
#include"TextureHolder.h"
#include<iostream>
Bike::Bike(const Vector2& pos, float speed) : Obstacle(pos, speed), numsFrame(26), curFrame(0),frameTime(0.0f) {
    // Load bike frames
    for (int i = 0; i < numsFrame; i++){
        txt.push_back(&TextureHolder::getHolder().get((Textures::ID)(Textures::BIKE_1 + i)));
    }
}

Bike::~Bike() {
}

void Bike::update(float k){
    this->setPos(this->getPos().x,k);
}


void Bike::draw() {
    //std::cerr << "Bike " << position.y << std::endl;
    frameTime += GetFrameTime();
    if (frameTime >= 0.1f) {  // Change this value to control the frame rate
        frameTime = 0.0f;
        curFrame = (curFrame + 1) % numsFrame;
    }


    Vector2 tmp = this->getPos();
    // Move horizontally based on some speed (adjust as needed)
    tmp.x += this->getSpeed() * frameTime * 10;
    setPos(tmp.x,tmp.y);
    if (checkOutOfScreen()){
        setPos(0,tmp.y);
    }

    float scale = 0.3f;

    // Draw the current frame of the sprite at the updated position with size
    DrawTextureEx(*txt[curFrame],this->getPos(), 0.0f, scale, WHITE);

}