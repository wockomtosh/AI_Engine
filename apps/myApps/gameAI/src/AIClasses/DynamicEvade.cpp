#include "DynamicEvade.h"

DynamicEvade::DynamicEvade(AIComponent* self, Rigidbody* evadeTarget, float evadeRadius, float decay)	:
	self(self), evadeTarget(evadeTarget), evadeRadius(evadeRadius), decay(decay) {}

DynamicEvade::~DynamicEvade()
{
	//Evade target points to some object, so don't delete it here
}

Acceleration DynamicEvade::getSteering()
{
	return Acceleration();
}
