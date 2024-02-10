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
	
	Vector2 forward = Vector2::getVectorFromAngle(self->body->orientation);
	//Using velocity as "forward" seems to make it just move in a straight line
	//Vector2 forward = self->body->velocity.normalize();
	
	//TODO: What is actually happening here?
	Vector2 wanderTargetPosition = self->body->position + (forward * wanderOffset) + (forward * wanderRadius);

	float binomial = randomBinomial();
	float wanderRadiusRotation = binomial * wanderRate;

	wanderTargetPosition = wanderTargetPosition - wanderRadiusRotation;

	if (seek)
	{
		delete seek;
	}
	//A big part of my issue is that DynamicSeek is controlling the orientation, but DynamicWander should be controlling that
	//Seek the location, but align to that location differently
	seek = new DynamicSeek(wanderTargetPosition, self, false);
	Acceleration steering = seek->getSteering();

	//This helps make it more like wander but it's spinning clockwise the entire time...
	steering.angular = DynamicAlign::face(self, wanderTargetPosition, 10, 10, .1);

	return steering;
}
