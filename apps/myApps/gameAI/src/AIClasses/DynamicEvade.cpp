#include "DynamicEvade.h"

DynamicEvade::DynamicEvade(AIComponent* self, Rigidbody* evadeTarget, float evadeRadius, float decay)	:
	self(self), evadeTarget(evadeTarget), evadeRadius(evadeRadius), decay(decay) {}

DynamicEvade::~DynamicEvade()
{
	//Evade target points to some object, so don't delete it here
}

Acceleration DynamicEvade::getSteering()
{
	Vector2 vectorToTarget = evadeTarget->position - self->body->position;
	float distanceToTarget = vectorToTarget.getMagnitude();
	if (distanceToTarget == 0)
	{
		return { Vector2(self->maxAccel, 0), 0 };
	}

	Vector2 fleeVector = Vector2();

	if (distanceToTarget < evadeRadius)
	{
		float repulsion = decay / ((distanceToTarget * distanceToTarget) / distanceToTarget);

		fleeVector = DynamicSeek::seek(evadeTarget->position, self) * -1 * repulsion;
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
		float repulsion = decay / (distanceToTarget * distanceToTarget);

		fleeVector = DynamicSeek::seek(evadeTarget->position, self) * -1 * repulsion;
	}

	return fleeVector;
}
