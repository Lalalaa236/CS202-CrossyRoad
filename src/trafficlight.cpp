#include "trafficlight.h"

// Constructor and Destructor

TrafficLight::TrafficLight() {
    this->lightState = false;
    this->timer = 0.0;
    this->redTimer = 5.0;
    this->greenTimer = 7.0;
    
    red = &TextureHolder::getHolder().get(Textures::RED_LIGHT);
    yellow = &TextureHolder::getHolder().get(Textures::YELLOW_LIGHT);
    green = &TextureHolder::getHolder().get(Textures::GREEN_LIGHT);
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

// Methods

void TrafficLight::draw() {
    // TODO: Draw the traffic light
}

void TrafficLight::update() {
    // TODO: Update the traffic light
}