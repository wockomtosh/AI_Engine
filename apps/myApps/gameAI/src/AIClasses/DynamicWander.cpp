#include "DynamicWander.h"
#include "DynamicAlign.h"
#include <random>
#include <iostream>

DynamicWander::DynamicWander(AIComponent* self, float wanderOffset, float wanderRadius, float wanderRate) :
	self(self), wanderOffset(wanderOffset), wanderRadius(wanderRadius), wanderRate(wanderRate) 
{
	seek = nullptr;
}

DynamicWander::~DynamicWander() {}

float randFloat(float max = 1)
{
	return static_cast<float>(rand()) / static_cast<float>(RAND_MAX / max);
}

float randomBinomial()
{	
	return randFloat() - randFloat();
}

Acceleration DynamicWander::getSteering()
{
	Vector2 forward = Vector2::getUnitVectorFromAngle(self->body->orientation);
	
	Vector2 wanderAreaCenter = self->body->position + (forward * wanderOffset);

	Vector2 wanderTargetPosition = wanderAreaCenter + (forward * wanderRadius);

	float wanderRadiusRotation = randomBinomial() * wanderRate;

	//We need to rotate our wanderTargetPosition around wanderAreaCenter
	wanderTargetPosition = wanderTargetPosition.rotateAroundPoint(wanderAreaCenter, wanderRadiusRotation);

	if (seek)
	{
		delete seek; //When I get rid of this it seems to not leak memory. Why?
	}
	//Seek the location, but align to that location differently
	seek = new DynamicSeek(wanderTargetPosition, self, false);
	Acceleration steering = seek->getSteering();

	steering.angular = DynamicAlign::face(self, wanderTargetPosition, 1, .5, .1);

	return steering;
}
