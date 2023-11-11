#pragma once
#include "Obstacle.h"
class Car : public Obstacle
{
private: 
public: 
	Car(); 
	virtual bool checkType();
};