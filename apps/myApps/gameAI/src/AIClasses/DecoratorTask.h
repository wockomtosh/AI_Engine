#pragma once
#include "Task.h"
#include "Decoration.h"

class DecoratorTask : public Task {
public:
	DecoratorTask(int i_id, Task* child);

	Status run(Tick* t);

	virtual Status runChild(Tick* t, Task* childTask);
};