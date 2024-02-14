#pragma once
#include "ISteeringBehavior.h"
#include "../Components/AIComponent.h"
#include "DynamicEvade.h"
#include <vector>

class DynamicSeparation : public ISteeringBehavior {
	AIComponent* self;
	//Later I'll probably want to be able to have this be Rigidbodies OR AIComponents, or maybe construct a vector of bodies from components
	std::vector<AIComponent*> targets; 
	float personalRadius;

public:
	DynamicSeparation(AIComponent* self, std::vector<AIComponent*> targets, float personalRadius = 200);
	~DynamicSeparation();

	Acceleration getSteering();
};