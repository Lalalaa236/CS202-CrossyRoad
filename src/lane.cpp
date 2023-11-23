#include "lane.h"

using namespace std;

Lane::Lane(float y, int id) {
    this->y= 100;
    this->id= 0;
}

void Lane::addObstacle(Obstacle* obstacle) {
    obstacles.push_back(obstacle);
}

void Lane::draw() {

}

Lane::~Lane() {
    while(obstacles.size()) {
        delete obstacles.front();
        obstacles.pop_front();
    }
}

