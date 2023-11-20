#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H

#include "raylib.h"
#include <cassert>

class TrafficLight {
private:
    bool lightState = false;    // false = red, true = green
    double timer = 0.0;         // timer for light state
    double redTimer = 0.0, greenTimer = 0.0;    // timers for red and green lights

public:
    // Constructor and Destructor
    TrafficLight();
    TrafficLight(bool state, double redTimer, double greenTimer);
    virtual ~TrafficLight();

    // Getters and Setters
    bool getLightState() const;
    void setLightState(bool state);
    double getTimer() const;

    // Methods
    void draw();
    void update();
};

#endif // TRAFFIC_LIGHT_H
