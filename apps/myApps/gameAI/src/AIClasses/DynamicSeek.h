#pragma once
#include "ISteeringBehavior.h"

class DynamicSeek : ISteeringBehavior {


public:
	DynamicSeek();
	~DynamicSeek();
	Acceleration getSteering();
};