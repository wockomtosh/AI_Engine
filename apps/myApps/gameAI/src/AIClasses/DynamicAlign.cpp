#include "DynamicAlign.h"
#include <math.h>
#include "../DataTypes/Orientation.h"

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
	//We could call our static function here, but my hunch is that is is more efficient... 
	//Not sure. Lots of behaviors that would use this would need to create a new one every frame, which seems less efficient than the static function...
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
	return align(self, targetOrientation, slowRadius, targetRadius, timeToTargetRotation);
}

float DynamicAlign::face(AIComponent* self, Vector2 target, float slowRadius, float targetRadius, float timeToTargetRotation)
{
	Vector2 targetDirection = target - self->body->position;
	float targetOrientation = atan2(targetDirection.y, targetDirection.x) * (180 / 3.1415);
	//atan2 gives 0 orientation as pointing to the right, so we need to offset that properly.
	targetOrientation += 90;
	targetOrientation = Orientation::clampOrientation(targetOrientation);

	return align(self, targetOrientation, slowRadius, targetRadius, timeToTargetRotation);
}

float DynamicAlign::align(AIComponent* self, float targetOrientation, float slowRadius, float targetRadius, float timeToTargetRotation)
{
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