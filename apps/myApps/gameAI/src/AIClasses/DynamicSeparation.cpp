#include "DynamicSeparation.h"


DynamicSeparation::DynamicSeparation(AIComponent* self, std::vector<AIComponent*> targets, float personalRadius) :
	self(self), targets(targets), personalRadius(personalRadius) {}

DynamicSeparation::~DynamicSeparation()
{
}

Acceleration DynamicSeparation::getSteering()
{
	Vector2 output = Vector2();

	for (int i = 0; i < targets.size(); i++)
	{
		output += DynamicEvade::evade(self, targets[i]->body, personalRadius);
	}

	return Acceleration(output, 0);
}
