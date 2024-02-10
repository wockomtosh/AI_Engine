#include "DynamicWander2.h"
#include "DynamicAlign.h"
#include <random>
#include <iostream>

DynamicWander2::DynamicWander2(AIComponent* self, float wanderOffset) :
	self(self), wanderOffset(wanderOffset) 
{
	seek = nullptr;
}

DynamicWander2::~DynamicWander2() {}

float randFloat(float max = 1)
{
	return static_cast<float>(rand()) / static_cast<float>(RAND_MAX / max);
}

float randomBinomial()
{	
	return randFloat() - randFloat();
}

Acceleration DynamicWander2::getSteering()
{
	Vector2 selfPosition = self->body->position;

	//Just move forward
	Vector2 forward = Vector2::getUnitVectorFromAngle(self->body->orientation);
	Vector2 wanderTargetPosition = self->body->position + (forward * wanderOffset);

	if (seek)
	{
		delete seek;
	}
	seek = new DynamicSeek(wanderTargetPosition, self, false);

	Acceleration steering = seek->getSteering();

	//Accelerate according to randomBinomial
	float wanderRotation = randomBinomial() * self->maxAngular;

	steering.angular = wanderRotation;

	return steering;
}
