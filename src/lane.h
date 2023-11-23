#ifndef LANE_H
#define LANE_H

#include "Obstacle.h"
#include "TrafficLight.h"
#include <deque>

using namespace std;

class Lane {
    public:
        Lane(float y, int id);
        void addObstacle(Obstacle* obstacle);
        void draw();
        ~Lane();

    private:
        float y;
        int id;
        deque <Obstacle*> obstacles;
        TrafficLight* trafficLight;
};

#endif