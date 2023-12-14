#include "trafficlight.h"
#include <iostream>

// Constructor and Destructor

TrafficLight::TrafficLight(float x, float y) : position({x, y}) {
    this->timer = 0.0;
    this->redTimer = 5.0;
    this->greenTimer = 7.0;

    red = &TextureHolder::getHolder().get(Textures::RED_LIGHT);
    yellow = &TextureHolder::getHolder().get(Textures::YELLOW_LIGHT);
    green = &TextureHolder::getHolder().get(Textures::GREEN_LIGHT);

    int random = rand() % 2;
    random == 0 ? this->lightState = false : this->lightState = true;
}

TrafficLight::TrafficLight(bool state, double redTimer, double greenTimer) {
    // Make sure the timers are not negative
    assert(redTimer >= 0);
    assert(greenTimer >= 0);

    this->lightState = state;
    this->timer = 0.0;
    this->redTimer = redTimer;
    this->greenTimer = greenTimer;

    red = &TextureHolder::getHolder().get(Textures::RED_LIGHT);
    yellow = &TextureHolder::getHolder().get(Textures::YELLOW_LIGHT);
    green = &TextureHolder::getHolder().get(Textures::GREEN_LIGHT);
}

TrafficLight::~TrafficLight() {
    // Nothing to do here
}

// Getters and Setters

bool TrafficLight::getLightState() const {
    return this->lightState;
}

void TrafficLight::setLightState(bool state) {
    this->lightState = state;
}

double TrafficLight::getTimer() const {
    return this->timer;
}

std::pair<float, float> TrafficLight::getPosition() const {
    return this->position;
}

// Methods

void TrafficLight::draw() {
    if (!lightState)
        DrawTextureEx(*red, {position.first, position.second - 40}, 0, 1, WHITE);
    else
        DrawTextureEx(*green, {position.first, position.second - 40}, 0, 1, WHITE);
}

void TrafficLight::update() {
    this->timer += GetFrameTime();
    if(this->timer != GetFrameTime() && this->isChanged)
        this->isChanged = false;

    if(!lightState) {
        if(timer >= redTimer) {
            lightState = true;
            isChanged = true;
            timer = 0.0f;
        }
    } 
    else {
        if(timer >= greenTimer) {
            lightState = false;
            isChanged = true;
            timer = 0.0f;
        }
    }
}

void TrafficLight::setY(float y) {
    this->position.second = y;
}

bool TrafficLight::getIsChanged() const {
    return this->isChanged;
}