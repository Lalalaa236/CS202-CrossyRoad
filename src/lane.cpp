#include "lane.h"

Lane::Lane(float y, int id) 
: y(y)
{
    id = rand() % 2;
    switch(id)
    {
        case 0:
            texture = &TextureHolder::getHolder().get(Textures::ROAD);
            trafficLight = new TrafficLight();
            break;
        case 1:
            texture = &TextureHolder::getHolder().get(Textures::GRASS);
            trafficLight = nullptr;
            break;
        default:
            texture = nullptr;
            trafficLight = nullptr;
            break;
    }
}

void Lane::addObstacle(Obstacle* obstacle) {
    obstacles.push_back(obstacle);
}

void Lane::draw() {
    DrawTextureEx(*texture, {0, y}, 0, 1, WHITE);
    if (trafficLight != nullptr) {
        trafficLight->draw();
    }
    // for (auto obstacle : obstacles) {
    //     obstacle->draw();
    // }
}

Lane::~Lane() {
    while(obstacles.size()) {
        delete obstacles.front();
        obstacles.pop_front();
    }
    delete trafficLight;
}

void Lane::setY(float y) 
{
    this->y = y;
}

float Lane::getY() const
{
    return y;
}