#pragma once
#include <vector>
#include <algorithm>
#include "ISteeringBehavior.h"
#include "../Components/AIComponent.h"
#include "DynamicArrive.h"
#include "DynamicVelocityMatch.h"
#include "DynamicSeparation.h"
#include "DynamicAlign.h"

//Do I want these? Maybe later. Maybe useful just as a location to define a bunch of values?
//struct SeparationParams {
//	float weight = 1;
//	float evadeRadius = 100;
//	float decay = 1;
//};
//
//struct ArriveParams {
//	float weight = .8;
//	float slowRadius = 100;
//	float targetRadius = 10;
//	float timeToTargetVelocity = .5;
//};
//
//struct VelocityMatchParams {
//	float weight = .6;
//	float timeToTargetVelocity = .5;
//};

class DynamicFlocking : public ISteeringBehavior {
	AIComponent* self;
	std::vector<AIComponent*> flock;
	float separationWeight;
	float arriveWeight;
	float velocityMatchWeight;

	DynamicSeparation* separationBehavior;

public:
	DynamicFlocking(AIComponent* self, std::vector<AIComponent*> flock, float separationWeight = 5000, float arriveWeight = .8, float velocityMatchWeight = .6);
	~DynamicFlocking();

	Acceleration getSteering();
};