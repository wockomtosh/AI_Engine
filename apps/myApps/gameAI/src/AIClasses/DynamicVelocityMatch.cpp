#include "DynamicVelocityMatch.h"
#include "DynamicAlign.h"

DynamicVelocityMatch::DynamicVelocityMatch(AIComponent* self, Vector2 targetVelocity, float timeToTargetVelocity) :
	self(self), targetVelocity(targetVelocity), timeToTargetVelocity(timeToTargetVelocity)
{
}

DynamicVelocityMatch::~DynamicVelocityMatch()
{
}

Acceleration DynamicVelocityMatch::getSteering()
{
	float angular = DynamicAlign::lookWhereYouAreGoing(self, 20, 2, .1);

	Vector2 targetAccel = (targetVelocity - self->body->velocity) / timeToTargetVelocity;
	return { targetAccel, angular };
}

Vector2 DynamicVelocityMatch::velocityMatch(AIComponent* self, Vector2 targetVelocity, float timeToTargetVelocity)
{
	Vector2 targetAccel = (targetVelocity - self->body->velocity) / timeToTargetVelocity;
	return targetAccel;
}
