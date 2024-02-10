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
	DynamicArrive2(AIComponent* self, Vector2 target);
	DynamicArrive2(AIComponent* self, Vector2 target, float slowRadius, float targetRadius, float timeToTargetVelocity);
	~DynamicArrive2();
	Acceleration getSteering();
};