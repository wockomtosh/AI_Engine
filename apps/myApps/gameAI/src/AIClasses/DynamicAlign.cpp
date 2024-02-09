#include "DynamicAlign.h"
#include <math.h>

DynamicAlign::DynamicAlign(AIComponent* self, float target) :
	self(self), target(target)
{
	slowRadius = 20;
	targetRadius = 2;
	timeToTargetRotation = .1;
}

DynamicAlign::DynamicAlign(AIComponent* self, float target, float slowRadius, float targetRadius, float timeToTargetRotation) :
	self(self), target(target), slowRadius(slowRadius), targetRadius(targetRadius), timeToTargetRotation(timeToTargetRotation) {}

DynamicAlign::~DynamicAlign() {}

Acceleration DynamicAlign::getSteering()
{
	float orientationDist = target - self->body->orientation;
	float targetSpeedDirection = 1;

	//Account for different directions that give the shortest rotation
	if (orientationDist > 180 || (orientationDist < 0 && orientationDist > -180))
	{
		targetSpeedDirection = -1;
	}

	float targetAccel;

	orientationDist = fabsf(orientationDist);

	if (orientationDist > slowRadius)
	{
		//Just rotate at max accel in the correct direction
		targetAccel = targetSpeedDirection * self->maxAngular;
	}
	else if (orientationDist <= targetRadius)
	{
		//When we're inside the targetRadius we're targeting 0 speed
		targetAccel = (0 - self->body->rotation) / timeToTargetRotation;
	}
	else
	{
		//When we're inside the slow radius calculate target speed and match that
		float speedScalingFactor = orientationDist / slowRadius;
		float targetSpeed = targetSpeedDirection * speedScalingFactor * self->body->maxRotation;
		targetAccel = (targetSpeed - self->body->rotation) / timeToTargetRotation;
	}
	return { Vector2(), targetAccel };
}

float DynamicAlign::lookWhereYouAreGoing(AIComponent* self, float slowRadius, float targetRadius, float timeToTargetRotation)
{
	float targetOrientation = self->body->getOrientationOfMovement();
	float orientationDist = targetOrientation - self->body->orientation;
	float targetSpeedDirection = 1;

	//Account for different directions that give the shortest rotation
	if (orientationDist > 180 || (orientationDist < 0 && orientationDist > -180))
	{
		targetSpeedDirection = -1;
	}

	float targetAccel;

	orientationDist = fabsf(orientationDist);

	if (orientationDist > slowRadius)
	{
		//Just rotate at max accel in the correct direction
		targetAccel = targetSpeedDirection * self->maxAngular;
	}
	else if (orientationDist <= targetRadius)
	{
		//When we're inside the targetRadius we're targeting 0 speed
		targetAccel = (0 - self->body->rotation) / timeToTargetRotation;
	}
	else
	{
		//When we're inside the slow radius calculate target speed and match that
		float speedScalingFactor = orientationDist / slowRadius;
		float targetSpeed = targetSpeedDirection * speedScalingFactor * self->body->maxRotation;
		targetAccel = (targetSpeed - self->body->rotation) / timeToTargetRotation;
	}
	return targetAccel;

}