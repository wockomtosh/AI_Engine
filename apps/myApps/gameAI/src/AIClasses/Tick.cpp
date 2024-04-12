#include "Tick.h"
#include "Task.h"
#include <iostream>

void Tick::open(Task* t)
{
	std::cout << "Opening Task: " << t->id << std::endl;
}

void Tick::enter(Task* t)
{
	std::cout << "Entering Task: " << t->id << std::endl;
}

void Tick::execute(Task* t)
{
	std::cout << "Executing Task: " << t->id << std::endl;
}

void Tick::exit(Task* t)
{
	std::cout << "Exiting Task: " << t->id << std::endl;
}

//I'm not positive yet how I want to track/handle statuses, but I definitely want to reset child statuses after closing.
void Tick::close(Task* t)
{
	std::cout << "Closing Task, resetting child statuses: " << t->id << std::endl;

	for (Task* child : t->children)
	{
		child->status = Status::none;
	}
}
