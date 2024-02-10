#pragma once
#include "ISteeringBehavior.h"
#include "../Components/AIComponent.h"
#include "DynamicSeek.h"

class DynamicWander3 : public ISteeringBehavior {
	AIComponent* self;
	float wanderOffset;
	float wanderRadius;
	float wanderRate;

	DynamicSeek* seek;

public:
	DynamicWander3(AIComponent* self, float wanderOffset = 50, float wanderRadius = 60, float wanderRate = 100);
	~DynamicWander3();
	Acceleration getSteering();
};