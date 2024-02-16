#include "DynamicFlocking.h"

DynamicFlocking::DynamicFlocking(AIComponent* self, std::vector<AIComponent*> flock, float separationWeight, float seekWeight, float velocityMatchWeight) :
	self(self), flock(flock), separationWeight(separationWeight), seekWeight(seekWeight), velocityMatchWeight(velocityMatchWeight)
{
	std::vector<AIComponent*> flockExceptSelf = flock; //TODO exclude self
	flockExceptSelf.erase(std::remove(flockExceptSelf.begin(), flockExceptSelf.end(), self));

	separationBehavior = new DynamicSeparation(self, flockExceptSelf, 100); 
}

DynamicFlocking::~DynamicFlocking()
{
	delete separationBehavior;
}

Acceleration DynamicFlocking::getSteering()
{
	Acceleration separationOutput = separationBehavior->getSteering();

	float leaderMassWeight = 100;
	float leaderVelocityWeight = 20;
	Vector2 centerOfFlock = Vector2();
	Vector2 flockVelocity = Vector2();
	for (int i = 0; i < flock.size(); i++)
	{
		if (flock[i]->tag == FLOCK_LEADER)
		{
			centerOfFlock += flock[i]->body->position * leaderMassWeight;
			flockVelocity += flock[i]->body->velocity * leaderVelocityWeight;
		}
		else 
		{
			centerOfFlock += flock[i]->body->position;
			flockVelocity += flock[i]->body->velocity;
		}
	}

	centerOfFlock /= flock.size() + leaderMassWeight;
	flockVelocity /= flock.size() + leaderVelocityWeight;

	Vector2 seekOutput = DynamicSeek::seek(centerOfFlock, self);
	//My seek gets multiplied by max accel, so this needs to as well if we want them to be in the same range.
	//Otherwise seek is disproportionately larger than velocityMatch
	Vector2 velocityMatchOutput = DynamicVelocityMatch::velocityMatch(self, flockVelocity) * self->maxAccel; 

	float angular = DynamicAlign::lookWhereYouAreGoing(self);

	//Increasing velocityMatchWeight makes them join up with the flock more smoothly rather than crashing into the side of the flock.
	//However, it also makes it so that they don't stick as closely together.
	Acceleration combinedOutput = { separationOutput.linear * separationWeight + seekOutput * seekWeight + velocityMatchOutput * velocityMatchWeight,
								    angular };

	return combinedOutput;
}
