#include "DynamicEvade.h"

DynamicEvade::DynamicEvade(AIComponent* self, Rigidbody* evadeTarget, float evadeRadius, float decay) :
	self(self), evadeTarget(evadeTarget), evadePosition(evadeTarget->position), evadeRadius(evadeRadius), decay(decay) {}

DynamicEvade::DynamicEvade(AIComponent* self, Vector2 evadePosition, float evadeRadius, float decay) :
	self(self), evadeTarget(nullptr), evadePosition(evadePosition), evadeRadius(evadeRadius), decay(decay) {}

DynamicEvade::~DynamicEvade()
{
	//Evade target points to some object, so don't delete it here
}

Acceleration DynamicEvade::getSteering()
{
	if (evadeTarget != nullptr)
	{
		evadePosition = evadeTarget->position;
	}
	Vector2 vectorToTarget = evadePosition - self->body->position;
	float distanceToTarget = vectorToTarget.getMagnitude();
	if (distanceToTarget == 0)
	{
		return { Vector2(self->maxAccel, 0), 0 };
	}

	Vector2 fleeVector = Vector2();

	if (distanceToTarget < evadeRadius)
	{
		float repulsion = decay / ((distanceToTarget * distanceToTarget) / distanceToTarget);

		fleeVector = DynamicSeek::seek(evadePosition, self) * -1 * repulsion;
	}

	float angular = DynamicAlign::lookWhereYouAreGoing(self);

	return Acceleration(fleeVector, angular);
}

Vector2 DynamicEvade::evade(AIComponent* self, Rigidbody* evadeTarget, float evadeRadius, float decay)
{
	Vector2 vectorToTarget = evadeTarget->position - self->body->position;
	float distanceToTarget = vectorToTarget.getMagnitude();
	if (distanceToTarget == 0)
	{
		return Vector2(self->maxAccel, 0);
	}

	Vector2 fleeVector = Vector2();

	if (distanceToTarget < evadeRadius)
	{
		//Inverse square patter works great if you're less than 1. So let's scale it down
		float adjustedDistance = 1 - ((evadeRadius - distanceToTarget) / evadeRadius);
		float repulsion = decay / (adjustedDistance * adjustedDistance);

		fleeVector = DynamicSeek::seek(evadeTarget->position, self) * -1 * repulsion;
	}

	return fleeVector;
}

Vector2 DynamicEvade::evade(AIComponent* self, Vector2 evadePosition, float evadeRadius, float decay)
{
	Vector2 vectorToTarget = evadePosition - self->body->position;
	float distanceToTarget = vectorToTarget.getMagnitude();
	if (distanceToTarget == 0)
	{
		return Vector2(self->maxAccel, 0);
	}

	Vector2 fleeVector = Vector2();

	if (distanceToTarget < evadeRadius)
	{
		//Inverse square patter works great if you're less than 1. So let's scale it down
		float adjustedDistance = 1 - ((evadeRadius - distanceToTarget) / evadeRadius);
		float repulsion = decay / (adjustedDistance * adjustedDistance);

		fleeVector = DynamicSeek::seek(evadePosition, self) * -1 * repulsion;
	}

	return fleeVector;
}
