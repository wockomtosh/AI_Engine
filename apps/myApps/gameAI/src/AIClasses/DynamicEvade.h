#pragma once
#include "ISteeringBehavior.h"
#include "../Components/AIComponent.h"
#include "DynamicSeek.h"
#include "DynamicAlign.h"
#include <utility>

class DynamicEvade : public ISteeringBehavior {
	AIComponent* self;
	Rigidbody* evadeTarget;
	Vector2 evadePosition;
	float evadeRadius;
	float decay;

public:
	DynamicEvade(AIComponent* self, Rigidbody* evadeTarget, float evadeRadius = 200, float decay = 1);
	DynamicEvade(AIComponent* self, Vector2 evadePosition, float evadeRadius = 200, float decay = 1);
	~DynamicEvade();
	Acceleration getSteering();

	static Vector2 evade(AIComponent* self, Rigidbody* evadeTarget, float evadeRadius = 200, float decay = 1);
	static Vector2 evade(AIComponent* self, Vector2 evadePosition, float evadeRadius = 200, float decay = 1);
};