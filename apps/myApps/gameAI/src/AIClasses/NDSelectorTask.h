#pragma once
#include "Task.h"
#include <random>

//A non-deterministic selector
class NDSelectorTask : public Task {
	//Used when we have a task that is running so we can go right back to it
	Task* lastRunning;
	//Used to keep track of which tasks we have already visited so that we don't double dip until we finish
	std::vector<int> randomList;
	std::default_random_engine rng;

public:
	NDSelectorTask(int i_id, std::vector<Task*> i_children);

	Status run(Tick* t);
};