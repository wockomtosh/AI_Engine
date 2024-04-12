#pragma once
#include "Task.h"

class SequenceTask : public Task {

public:
	SequenceTask(int i_id, std::vector<Task*> i_children);

	Status run(Tick* t);
};