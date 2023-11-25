#include "Map.h"
#include <iostream>

Map::Map(float speed)
: speed(speed)
{
    for(int i = 0; i < 12; ++i)
    {
        Lane* lane = new Lane(-158.0f + i * 95.0f, i);
        lanes.push_back(lane);
    }
}

void Map::draw()
{
    for(auto lane : lanes){
        lane->draw();
        lane->update();
    }
    // static int i = 0;
    // if(i++ == 0)
    //     std::cout << "Map draw called" << std::endl;
    // std::cout << lanes[0]->getY() << std::endl;
}

void Map::update()
{
    for(auto lane : lanes){
        lane->setY(lane->getY() + speed);
    }
    if(lanes.back()->getY() > 982.0f)
    {
        delete lanes.back();
        lanes.pop_back();
        Lane* lane = new Lane(lanes.front()->getY() - 95.0f, 0);
        lanes.push_front(lane);
        // std::cout << lanes.front()->getY() << std::endl;
    }
    // static int i = 0;
    // if(i++ == 0)
    //     std::cout << "Map update called" << std::endl;
}

void Map::setSpeed(float speed)
{
    this->speed = speed;
}

Map::~Map()
{
    for(auto lane : lanes)
    {
        delete lane;
    }
}