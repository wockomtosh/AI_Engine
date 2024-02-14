#include "DynamicFlocking.h"

DynamicFlocking::DynamicFlocking(AIComponent* self, std::vector<AIComponent*> flock, float separationWeight, float arriveWeight, float velocityMatchWeight) :
	self(self), flock(flock), separationWeight(separationWeight), arriveWeight(arriveWeight), velocityMatchWeight(velocityMatchWeight)
{
	std::vector<AIComponent*> flockExceptSelf = flock; //TODO exclude self
	flockExceptSelf.erase(std::remove(flockExceptSelf.begin(), flockExceptSelf.end(), self));

	separationBehavior = new DynamicSeparation(self, flockExceptSelf); 
}

DynamicFlocking::~DynamicFlocking()
{
	delete separationBehavior;
}

Acceleration DynamicFlocking::getSteering()
{
	Acceleration separationOutput = separationBehavior->getSteering();

	Vector2 centerOfFlock = Vector2();
	Vector2 flockVelocity = Vector2();
	for (int i = 0; i < flock.size(); i++)
	{
		//TODO: Weight the 'mass' of the leader
		centerOfFlock += flock[i]->body->position;
		flockVelocity += flock[i]->body->velocity;
	}

	centerOfFlock /= flock.size();
	flockVelocity /= flock.size();

	Vector2 arriveOutput = DynamicArrive::arrive(self, centerOfFlock, 10, 10, .1);	
	Vector2 velocityMatchOutput = DynamicVelocityMatch::velocityMatch(self, flockVelocity);

	float angular = DynamicAlign::lookWhereYouAreGoing(self);

	Acceleration combinedOutput = { separationOutput.linear * separationWeight + arriveOutput * arriveWeight + velocityMatchOutput * velocityMatchWeight,
								    angular };

	return combinedOutput;
}
