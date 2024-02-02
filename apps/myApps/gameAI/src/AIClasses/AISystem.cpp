#include "AISystem.h"

AISystem::AISystem(Rigidbody** rigidbodies, int numRigidbodies) : 
	rigidbodies(rigidbodies), numRigidbodies(numRigidbodies)
{
}

void AISystem::update()
{
	for (int i = 0; i < numRigidbodies; i++)
	{
		//GET STEERING FOR EACH RIGIDBODY
		//rigidbodies[i]->update(.0167, )
	}
}
