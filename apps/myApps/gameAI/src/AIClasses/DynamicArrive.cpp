#include "DynamicArrive.h"
#include <math.h>

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

float lookWhereYouAreGoing(AIComponent* self, float slowRadius, float targetRadius, float timeToTargetRotation)
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

	//TODO SPLIT THIS OUT INTO SOMETHING, A STATIC FUNCTION???

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

Acceleration DynamicArrive::getSteering()
{
	//TODO swap this for something different
	float angular = lookWhereYouAreGoing(self, 20, 2, .1);

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
	return Acceleration(targetAccel, angular);
}