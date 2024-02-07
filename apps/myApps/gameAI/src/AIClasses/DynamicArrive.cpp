#include "DynamicArrive.h"

DynamicArrive::DynamicArrive(AIComponent* self, Vector2 target) :
	self(self), target(target)
{
	slowRadius = 100;
	targetRadius = 10;
	timeToTargetVelocity = .5;
}

DynamicArrive::DynamicArrive(AIComponent* self, Vector2 target, float slowRadius, float targetRadius, float timeToTargetVelocity) :
	self(self), target(target), slowRadius(slowRadius), targetRadius(targetRadius), timeToTargetVelocity(timeToTargetVelocity) {}

DynamicArrive::~DynamicArrive()  {}

Acceleration DynamicArrive::getSteering()
{
	//TODO orient in the direction of travel
	Vector2 targetAccel;
	Vector2 targetVector = target - self->body->position;
	float distance = targetVector.getMagnitude();
	if (distance > slowRadius)
	{
		//Seek when we're outside the slow radius
		targetAccel = targetVector * self->maxAccel;
	}
	else if (distance <= targetRadius)
	{
		//When we're inside the targetRadius we're targeting 0 velocity
		targetAccel = (Vector2() - self->body->velocity) / timeToTargetVelocity;
	}
	else
	{
		//When we're inside the slow radius calculate target velocity and match that
		float speedScalingFactor = distance / slowRadius;
		float targetSpeed = speedScalingFactor * self->body->maxSpeed;
		Vector2 targetVelocity = targetVector.getVectorWithMagnitude(targetSpeed);
		targetAccel = (targetVelocity - self->body->velocity) / timeToTargetVelocity;
	}
	return Acceleration(targetAccel, 0);
}