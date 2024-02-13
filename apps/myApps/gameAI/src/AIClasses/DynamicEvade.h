#pragma once
#include "ISteeringBehavior.h"
#include "../Components/AIComponent.h"

class DynamicEvade : public ISteeringBehavior {
	AIComponent* self;
	Rigidbody* evadeTarget;
	float evadeRadius;
	float decay;

public:
	DynamicEvade(AIComponent* self, Rigidbody* evadeTarget, float evadeRadius = 200, float decay = 1);
	~DynamicEvade();
	Acceleration getSteering();
};