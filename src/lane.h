#ifndef LANE_H
#define LANE_H

#include "Obstacle.h"
#include "trafficlight.h"
#include <deque>
#include "TextureHolder.h"

class Lane {
    public:
        Lane(float y, float mapSpeed);
        ~Lane();

        void setY(float y);
        float getY() const;
        void setSpeed(float mapSpeed);
        
        void addObstacle(Obstacle* obstacle);
        void draw();
        void update();

    private:
        const Texture2D* texture;
        float y;
        float mapSpeed;
        std::deque<Obstacle*> obstacles;
        TrafficLight* trafficLight;
};

#endif