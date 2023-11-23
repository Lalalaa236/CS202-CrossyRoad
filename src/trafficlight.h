#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H

#include "TextureHolder.h"
#include <cassert>

class TrafficLight {
private:
    std::pair<float, float> position;   // position of traffic light
    bool lightState = false;    // false = red, true = green
    double timer = 0.0;         // timer for light state
    double redTimer = 0.0, greenTimer = 0.0;    // timers for red and green lights
    Texture2D* red;
    Texture2D* yellow;
    Texture2D* green;

public:
    // Constructor and Destructor
    TrafficLight(float x, float y);
    TrafficLight(bool state, double redTimer, double greenTimer);
    virtual ~TrafficLight();

    // Getters and Setters
    bool getLightState() const;
    void setLightState(bool state);
    double getTimer() const;
    std::pair<float, float> getPosition() const;
    void setY(float y);

    // Methods
    void draw();
    void update();
};

#endif // TRAFFIC_LIGHT_H
