#pragma once
#include "DecoratorTask.h"

class UntilFailDecorator : public DecoratorTask {
	//UntilFail doesn't need any unique state

public:
	//For UntilFail, if it succeeds we just return that it's running still (because we run until fail)
	Status runChild(Tick* t, Task* childTask)
	{
		Status status = childTask->run(t);

		if (status == Status::success)
		{
			return Status::running;
		}
		return status;
	}
};