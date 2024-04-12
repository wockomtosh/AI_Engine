#pragma once
#include "Task.h"

class SelectorTask : public Task {

public:
	SelectorTask(int i_id, std::vector<Task*> i_children);

	Status run(Tick* t);
};