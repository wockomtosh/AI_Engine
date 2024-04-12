#pragma once
#include <vector>
#include "Tick.h"

//Status enum lives in Tick because I decided that this will include tick rather than the other way around
struct Task {
	int id;
	std::vector<Task*> children;
	Status status = Status::none;

	virtual Status run(Tick* t) { return Status::failure; }
};