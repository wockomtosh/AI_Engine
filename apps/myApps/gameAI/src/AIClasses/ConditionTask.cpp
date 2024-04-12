#include "ConditionTask.h"

ConditionTask::ConditionTask(int i_id, Condition* i_condition) :
	condition(i_condition)
{
	id = i_id;
}

//Where do I call open/enter/exit/close on tick? 
//Maybe never since the default status is none, so we'll always just check the condition and move on
Status ConditionTask::run(Tick* t)
{
	t->open(this);
	if (condition->isTrue(t->blackboard))
	{
		t->close(this);
		return Status::success;
	}
	t->close(this);
	return Status::failure;
}
