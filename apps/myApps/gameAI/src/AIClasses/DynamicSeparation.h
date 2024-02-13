#pragma once
#include "ISteeringBehavior.h"

class DynamicSeparation : public ISteeringBehavior {

public:


	Acceleration getSteering();
};