#include "lane.h"
// #include <iostream>

Lane::Lane(float y, float mapSpeed) 
: y(y), mapSpeed(mapSpeed)
{
    static int cnt = 0;
    int random = rand() % 2;
    switch(random)
    {
        case 0:
            if(cnt == 5)
            {
                texture = &TextureHolder::getHolder().get(Textures::GRASS);
                trafficLight = nullptr;
                cnt = 0;
            }
            else
            {
                texture = &TextureHolder::getHolder().get(Textures::ROAD);
                trafficLight = new TrafficLight(5, this->y - 25);
                cnt++;
            }
            break;
        case 1:
            if(cnt == 3)
            {
                texture = &TextureHolder::getHolder().get(Textures::ROAD);
                trafficLight = new TrafficLight(5, this->y - 25);
                cnt = 0;
            }
            else
            {
                texture = &TextureHolder::getHolder().get(Textures::GRASS);
                trafficLight = nullptr;
                cnt++;
            }
            break;
        default:
            texture = nullptr;
            trafficLight = nullptr;
            break;
    }
    // static int i = 0;
}

void Lane::addObstacle(Obstacle* obstacle) 
{
    obstacles.push_back(obstacle);
}

void Lane::draw() 
{
    DrawTextureEx(*texture, {0, y}, 0, 1, WHITE);
    // DrawRectangleLinesEx({0, y, 1511, 95}, 2, BLACK);
    if(trafficLight)
    {
        trafficLight->setY(y - 25);
        trafficLight->draw();
    }
    // for (auto obstacle : obstacles) {
    //     obstacle->draw();
    // }
    // static int i = 0;
}

Lane::~Lane() 
{
    while(obstacles.size()) 
    {
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

void Lane::update() 
{
    if(trafficLight)
        trafficLight->update();
    // for (auto obstacle : obstacles) {
    //     obstacle->update();
    // }
    // static int i = 0;
}

void Lane::setSpeed(float mapSpeed) 
{
    this->mapSpeed = mapSpeed;
}