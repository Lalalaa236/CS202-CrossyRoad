#include "trafficlight.h"
#include <iostream>

// Constructor and Destructor

TrafficLight::TrafficLight(float x, float y, Type type) : position({x, y}), type(type) {
    this->timer = 0.0f;
    if(type == Type::ROAD) {
        this->redTimer = 5.0f;
        this->greenTimer = 7.0f;
        red = &TextureHolder::getHolder().get(Textures::RED_LIGHT);
        // yellow = &TextureHolder::getHolder().get(Textures::YELLOW_LIGHT);
        green = &TextureHolder::getHolder().get(Textures::GREEN_LIGHT);
        scale = 1.0f;
    }
    else if(type == Type::RAILWAY) {
        this->redTimer = 3.0f;
        this->greenTimer = 10.0f;
        red = &TextureHolder::getHolder().get(Textures::TRAIN_RED_LIGHT);
        // yellow = &TextureHolder::getHolder().get(Textures::YELLOW_LIGHT);
        green = &TextureHolder::getHolder().get(Textures::TRAIN_GREEN_LIGHT);
        scale = 0.15f;
    }

    int random = rand() % 2;
    random == 0 ? this->lightState = false : this->lightState = true;
}

TrafficLight::TrafficLight(bool state, double redTimer, double greenTimer, Type type) {
    // Make sure the timers are not negative
    assert(redTimer >= 0);
    assert(greenTimer >= 0);

    this->lightState = state;
    this->timer = 0.0;
    this->redTimer = redTimer;
    this->greenTimer = greenTimer;
    this->type = type;

    if(type == Type::ROAD) {
        red = &TextureHolder::getHolder().get(Textures::RED_LIGHT);
        // yellow = &TextureHolder::getHolder().get(Textures::YELLOW_LIGHT);
        green = &TextureHolder::getHolder().get(Textures::GREEN_LIGHT);
        scale = 1.0f;
    }
    else if(type == Type::RAILWAY) {
        red = &TextureHolder::getHolder().get(Textures::TRAIN_RED_LIGHT);
        // yellow = &TextureHolder::getHolder().get(Textures::YELLOW_LIGHT);
        green = &TextureHolder::getHolder().get(Textures::TRAIN_GREEN_LIGHT);
        scale = 0.15f;
    }
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
        DrawTextureEx(*red, {position.first, position.second - 40}, 0, scale, WHITE);
    else
        DrawTextureEx(*green, {position.first, position.second - 40}, 0, scale, WHITE);
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