#pragma once
#include "Task.h"
#include "Condition.h"

class ConditionTask : public Task {
	Condition* condition;

public:
	ConditionTask(int i_id, Condition* i_condition);

	Status run(Tick* t);
};