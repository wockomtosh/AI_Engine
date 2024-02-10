#pragma once
#include "ISteeringBehavior.h"
#include "../Components/AIComponent.h"

class DynamicArrive2 : public ISteeringBehavior {
	AIComponent* self;
	Vector2 target;
	float slowRadius;
	float targetRadius;
	float timeToTargetVelocity;

public:
	DynamicArrive2(AIComponent* self, Vector2 target, float slowRadius = 100, float targetRadius = 10, float timeToTargetVelocity = .5);
	~DynamicArrive2();
	Acceleration getSteering();
};