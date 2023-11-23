#include "Map.h"

Map::Map()
{
    speed = 0.5f;
    for(int i = 0; i < 12; ++i)
    {
        Lane* lane = new Lane(-158.0f + i * 95.0f, i);
        lanes.push_back(lane);
    }
}

void Map::draw()
{
    for(auto lane : lanes)
    {
        lane->draw();
    }
}

void Map::update()
{
    for(auto lane : lanes)
    {
        lane->setY(lane->getY() + speed);
    }
    if(lanes.back()->getY() > -982.0f)
    {
        delete lanes.back();
        lanes.pop_back();
        Lane* lane = new Lane(lanes.front()->getY() + 95.0f, 0);
        lanes.push_front(lane);
    }
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