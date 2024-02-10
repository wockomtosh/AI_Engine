#pragma once
#include "ISteeringBehavior.h"
#include "../Components/AIComponent.h"
#include "DynamicSeek.h"

class DynamicWander : public ISteeringBehavior {
	AIComponent* self;
	float wanderOffset;
	float wanderRadius;
	float wanderRate;

	DynamicSeek* seek;

public:
	DynamicWander(AIComponent* self, float wanderOffset = .5, float wanderRadius = .5, float wanderRate = 10);
	~DynamicWander();
	Acceleration getSteering();
};