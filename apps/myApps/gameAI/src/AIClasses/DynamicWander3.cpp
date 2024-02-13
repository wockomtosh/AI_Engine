#include "DynamicWander3.h"
#include "DynamicAlign.h"
#include <random>
#include <iostream>

DynamicWander3::DynamicWander3(AIComponent* self, float wanderOffset, float wanderRadius, float wanderRate) :
	self(self), wanderOffset(wanderOffset), wanderRadius(wanderRadius), wanderRate(wanderRate) 
{
	seek = nullptr;
}

DynamicWander3::~DynamicWander3() {}

float randFloat(float max = 1)
{
	return static_cast<float>(rand()) / static_cast<float>(RAND_MAX / max);
}

float randomBinomial()
{	
	return randFloat() - randFloat();
}

Acceleration DynamicWander3::getSteering()
{
	Vector2 forward = self->body->velocity.normalize();
	
	if (forward.isWithinRangeOf(Vector2(), .01, .01))
	{
		forward = Vector2::Up;
	}
	
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
	steering.angular = DynamicAlign::lookWhereYouAreGoing(self, 5, .5, .1);

	return steering;
}
