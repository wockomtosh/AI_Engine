#pragma once
#include "ISteeringBehavior.h"
#include "../Components/AIComponent.h"

class DynamicEmpty : public ISteeringBehavior {

public:
	DynamicEmpty() {}
	~DynamicEmpty() {}
	Acceleration getSteering() { return Acceleration(Vector2(), 0); }
};