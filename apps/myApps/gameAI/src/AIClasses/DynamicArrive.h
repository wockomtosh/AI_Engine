#pragma once
#include "ISteeringBehavior.h"
#include "../Components/AIComponent.h"

class DynamicArrive : public ISteeringBehavior {
	AIComponent* self;
	Vector2 target;
	float slowRadius;
	float targetRadius;
	float timeToTargetVelocity;

public:
	DynamicArrive(AIComponent* self, Vector2 target);
	DynamicArrive(AIComponent* self, Vector2 target, float slowRadius, float targetRadius, float timeToTargetVelocity);
	~DynamicArrive();
	Acceleration getSteering();
};