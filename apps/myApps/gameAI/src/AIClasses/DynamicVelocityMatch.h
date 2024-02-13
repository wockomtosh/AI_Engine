#pragma once
#include "ISteeringBehavior.h"
#include "../Components/AIComponent.h"

class DynamicVelocityMatch : public ISteeringBehavior {
	AIComponent* self;
	Vector2 targetVelocity;
	float timeToTargetVelocity;

public:
	DynamicVelocityMatch(AIComponent* self, Vector2 targetVelocity, float timeToTargetVelocity = .5);
	~DynamicVelocityMatch();
	Acceleration getSteering();

	static Vector2 velocityMatch(AIComponent* self, Vector2 targetVelocity, float timeToTargetVelocity = .5);
};