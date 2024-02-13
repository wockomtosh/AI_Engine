#include "DynamicVelocityMatch.h"

DynamicVelocityMatch::DynamicVelocityMatch(AIComponent* self, Vector2 targetVelocity, float timeToTargetVelocity) :
	self(self), targetVelocity(targetVelocity), timeToTargetVelocity(timeToTargetVelocity)
{
}

DynamicVelocityMatch::~DynamicVelocityMatch()
{
}

Acceleration DynamicVelocityMatch::getSteering()
{
	Vector2 targetAccel = (targetVelocity - self->body->velocity) / timeToTargetVelocity;
	return { targetAccel, 0 };
}

Vector2 DynamicVelocityMatch::velocityMatch(AIComponent* self, Vector2 targetVelocity, float timeToTargetVelocity)
{
	Vector2 targetAccel = (targetVelocity - self->body->velocity) / timeToTargetVelocity;
	return targetAccel;
}
