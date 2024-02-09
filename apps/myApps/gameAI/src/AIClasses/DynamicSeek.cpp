#include "DynamicSeek.h"
#include <math.h>

DynamicSeek::DynamicSeek(Vector2 target, AIComponent* self) :
	target(target), self(self)
{
}

DynamicSeek::~DynamicSeek()
{
	//DON'T delete the AIComponent because if we want to update our target we need a new DynamicSeek
	//Is this behavior pattern good? Idk, but we'll see.
}

float lookWhereYouAreGoing(AIComponent* self, float slowRadius, float targetRadius, float timeToTargetRotation)
{
	//This is the unique part for LookWhereYouAreGoing (maybe split the getOrientationOfMovement into that class too)
	float targetOrientation = self->body->getOrientationOfMovement();
	
	//TODO SPLIT THIS OUT INTO ALIGN, A STATIC FUNCTION???
	//I think I want my DynamicAlign to take in a target rather than a body, and then whatever is calling it will pass that in.

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

Acceleration DynamicSeek::getSteering()
{
	//TODO swap this for something different
	float angular = lookWhereYouAreGoing(self, 20, 2, .1);
	Vector2 seekVector = target - self->body->position;
	seekVector *= self->maxAccel;
	return Acceleration(seekVector, angular);
}
