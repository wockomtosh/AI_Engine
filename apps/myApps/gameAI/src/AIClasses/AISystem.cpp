#include "AISystem.h"

AISystem::AISystem(std::vector<AIComponent*> aiObjects) :
	aiObjects(aiObjects)
{
}

AISystem::~AISystem()
{
}

void AISystem::update(float dt)
{
	for (int i = 0; i < aiObjects.size(); i++)
	{
		aiObjects[i]->update(dt);
	}
}

std::vector<AIComponent*> AISystem::getAIObjects()
{
	return aiObjects;
}

void AISystem::replaceAIObjects(std::vector<AIComponent*> newAIObjects)
{
	aiObjects = newAIObjects;
}

void AISystem::addAIObject(AIComponent* object)
{
	aiObjects.push_back(object);
}
