#pragma once
#include "Task.h"
#include "Condition.h"

//For an alternative idea see the comment in DecoratorTask.h
class ConditionTask : public Task {
	Condition* condition;

public:
	ConditionTask(int i_id, Condition* i_condition);

	Status run(Tick* t);
};