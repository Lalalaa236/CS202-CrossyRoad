#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H

#include "TextureHolder.h"
#include <cassert>

class TrafficLight {
public:
    enum class Type
    {
        ROAD,
        RAILWAY
    };
    // Constructor and Destructor
    TrafficLight(float x, float y, Type type);
    TrafficLight(bool state, double redTimer, double greenTimer, Type type);
    virtual ~TrafficLight();

    // Getters and Setters
    bool getLightState() const;
    void setLightState(bool state);
    double getTimer() const;
    bool getIsChanged() const;
    std::pair<float, float> getPosition() const;
    void setY(float y);

    // Methods
    void draw();
    void update();

private:
    std::pair<float, float> position;        // position of traffic light
    bool lightState = false;                 // false = red, true = green
    bool isChanged = true;                  // check if the light state is changed
    float timer = 0.0f;                      // timer for light state
    float redTimer = 0.0f, greenTimer = 0.0f; // timers for red and green lights
    Type type;
    Texture2D *red;
    // Texture2D *yellow;
    Texture2D *green;
    float scale;
};

#endif // TRAFFIC_LIGHT_H
