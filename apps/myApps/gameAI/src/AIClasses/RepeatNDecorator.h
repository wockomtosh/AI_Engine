#pragma once
#include "DecoratorTask.h"

class RepeatNDecorator : public DecoratorTask {
	int n;
	int curN;

public:
	RepeatNDecorator(int i_id, Task* child, int i_n = 2) :
		DecoratorTask(i_id, child), n(i_n), curN(0) {}

	Status runChild(Tick* t, Task* childTask)
	{
		Status status = childTask->run(t);

		if (status == Status::success || status == Status::failure)
		{
			//We need to 'close' the child between runs
			//Because of how my close works usually we close the parent to reset the child, but decorators need special cases
			childTask->status = Status::none;
			curN++;
			if (curN < n)
			{
				return Status::running;
			}
			//JUST FOR THE RESET NEEDED IN THE ASSIGNMENT
			t->blackboard->setBool("victoryComplete", true);
			return status;
		}
		return status;
	}
};