#pragma once

#include "../Components/AIComponent.h"
#include <vector>

class AISystem {
	std::vector<AIComponent*> aiObjects;

public:
	AISystem(std::vector<AIComponent*> aiObjects);
	~AISystem();

	void update(float dt);

	std::vector<AIComponent*> getAIObjects();

	void replaceAIObjects(std::vector<AIComponent*> newAIObjects);
};