#include "trafficlight.h"
#include <iostream>

// Constructor and Destructor

TrafficLight::TrafficLight(float x, float y, Type type) : position({ x, y }), type(type) {
    this->timer = 0.0f;
    if (type == Type::ROAD) {
        this->redTimer = 5.0f;
        this->greenTimer = 7.0f;
        red = &TextureHolder::getHolder().get(Textures::RED_LIGHT);
        // yellow = &TextureHolder::getHolder().get(Textures::YELLOW_LIGHT);
        green = &TextureHolder::getHolder().get(Textures::GREEN_LIGHT);
        scale = 1.0f;
    }
    else if (type == Type::RAILWAY) {
        this->redTimer = 3.0f;
        this->greenTimer = 10.0f;
        red = &TextureHolder::getHolder().get(Textures::TRAIN_RED_LIGHT);
        // yellow = &TextureHolder::getHolder().get(Textures::YELLOW_LIGHT);
        green = &TextureHolder::getHolder().get(Textures::TRAIN_GREEN_LIGHT);
        scale = 0.15f;
    }

    int random = rand() % 2;
    random == 0 ? this->lightState = false : this->lightState = true;
    this->timer = (rand() % 100) / 10.0;
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

    if (type == Type::ROAD) {
        red = &TextureHolder::getHolder().get(Textures::RED_LIGHT);
        // yellow = &TextureHolder::getHolder().get(Textures::YELLOW_LIGHT);
        green = &TextureHolder::getHolder().get(Textures::GREEN_LIGHT);
        scale = 1.0f;
    }
    else if (type == Type::RAILWAY) {
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
    timer = 0.0f;
}

double TrafficLight::getTimer() const {
    return this->timer;
}

double TrafficLight::getRedTimer() const {
    return this->redTimer;
}

double TrafficLight::getGreenTimer() const {
    return this->greenTimer;
}

std::pair<float, float> TrafficLight::getPosition() const {
    return this->position;
}

// Methods

void TrafficLight::draw() {
    if (!lightState)
    {
        if (type == Type::ROAD)
        {
            if (timer >= redTimer * 5.0f / 8.0f)
            {
                if (drawTimer >= 0.3f)
                {
                    DrawTextureEx(*red, { position.first, position.second - 40 }, 0, scale, WHITE);
                    if (drawTimer >= 0.6f)
                        drawTimer = 0.0f;
                }
                else
                    DrawTextureEx(*green, { position.first, position.second - 40 }, 0, scale, WHITE);

            }
            else
                DrawTextureEx(*red, { position.first, position.second - 40 }, 0, scale, WHITE);
        }
        else
            DrawTextureEx(*red, { position.first, position.second - 40 }, 0, scale, WHITE);
    }
    else
    {
        if (type == Type::RAILWAY)
        {
            if (timer >= greenTimer * 5.0f / 8.0f)
            {
                if (drawTimer >= 0.3f)
                {
                    DrawTextureEx(*red, { position.first, position.second - 40 }, 0, scale, WHITE);
                    if (drawTimer >= 0.6f)
                        drawTimer = 0.0f;
                }
                else
                    DrawTextureEx(*green, { position.first, position.second - 40 }, 0, scale, WHITE);

            }
            else
                DrawTextureEx(*green, { position.first, position.second - 40 }, 0, scale, WHITE);
        }
        else
            DrawTextureEx(*green, { position.first, position.second - 40 }, 0, scale, WHITE);
    }
}

void TrafficLight::update() {
    timer += GetFrameTime();
    drawTimer += GetFrameTime();

    if (!lightState) {
        if (timer >= redTimer) {
            lightState = true;
            timer = 0.0f;
        }
    }
    else {
        if (timer >= greenTimer) {
            lightState = false;
            timer = 0.0f;
        }
    }
}

void TrafficLight::setY(float y) {
    this->position.second = y;
}

void TrafficLight::setTimer(float timer) {
    this->timer = timer;
}

void TrafficLight::setTimer(float redTimer, float greenTimer) {
    this->redTimer = redTimer;
    this->greenTimer = greenTimer;
}
