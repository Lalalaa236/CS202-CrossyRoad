#ifndef LANE_H
#define LANE_H

#include "Obstacle.h"
#include "trafficlight.h"
#include <deque>
#include "TextureHolder.h"

class Lane {
    public:
        Lane(float y, int id);
        void addObstacle(Obstacle* obstacle);
        void draw();
        ~Lane();

    private:
        const Texture2D* texture;
        float y;
        int id;
        std::deque<Obstacle*> obstacles;
        TrafficLight* trafficLight;
};

#endif