#include "lane.h"
#include <iostream>

Lane::Lane(float y, int id) 
: y(y)
{
    static int cnt = 0;
    this->id = rand() % 2;
    switch(this->id)
    {
        case 0:
            if(cnt == 5)
            {
                texture = &TextureHolder::getHolder().get(Textures::GRASS);
                cnt = 0;
            }
            else
            {
                texture = &TextureHolder::getHolder().get(Textures::ROAD);
                trafficLight = nullptr; //new TrafficLight();
                cnt++;
            }
            break;
        case 1:
            if(cnt == 3)
            {
                texture = &TextureHolder::getHolder().get(Textures::ROAD);
                trafficLight = nullptr;
                cnt = 0;
            }
            else
            {
                texture = &TextureHolder::getHolder().get(Textures::GRASS);
                trafficLight = nullptr; //new TrafficLight();
                cnt++;
            }
            break;
        default:
            texture = nullptr;
            trafficLight = nullptr;
            break;
    }
    // static int i = 0;
    // if(i++ < 12)
    //     std::cout << "Lane constructor called" << std::endl;
}

void Lane::addObstacle(Obstacle* obstacle) 
{
    obstacles.push_back(obstacle);
}

void Lane::draw() 
{
    DrawTextureEx(*texture, {0, y}, 0, 1, WHITE);
    // if(trafficLight) 
    //     trafficLight->draw();
    // for (auto obstacle : obstacles) {
    //     obstacle->draw();
    // }
    // static int i = 0;
    // if(i++ < 12)
    //     std::cout << "Lane draw called" << std::endl;
}

Lane::~Lane() 
{
    // while(obstacles.size()) 
    // {
    //     delete obstacles.front();
    //     obstacles.pop_front();
    // }
    // delete trafficLight;
}

void Lane::setY(float y) 
{
    this->y = y;
}

float Lane::getY() const
{
    return y;
}