#pragma once
#include "Condition.h"
#include "../Components/Rigidbody.h"

class CloseToTargetCondition : public Condition {
	float threshold;

public:
	CloseToTargetCondition(float i_threshold = 300) :
		threshold(i_threshold) {}

	bool isTrue(Blackboard* blackboard)
	{
		Vector2 characterPos = static_cast<Rigidbody*>(blackboard->getGeneric("character"))->position;
		Vector2 monsterPos = static_cast<Rigidbody*>(blackboard->getGeneric("monster"))->position;
		Vector2 distance = characterPos - monsterPos;
		return distance.getMagnitude() < threshold;
	}
};