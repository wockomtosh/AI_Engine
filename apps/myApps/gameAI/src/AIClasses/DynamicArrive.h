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
	DynamicArrive(AIComponent* self, Vector2 target, float slowRadius = 100, float targetRadius = 10, float timeToTargetVelocity = .5);
	~DynamicArrive();
	Acceleration getSteering();

	static Vector2 arrive(AIComponent* self, Vector2 target, float slowRadius = 100, float targetRadius = 10, float timeToTargetVelocity = .5);
};