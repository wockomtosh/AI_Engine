#pragma once
#include "Task.h"

//Alternative thought for decorators (or a different kind of hybrid condition task):
//Have decorators basically function as conditions. If the condition returns true then we run the child. Else, we return failure.
//This could make it easier to check conditions on each pass of the tree and have changes make it so that lower priority tasks are overridden.
//It's probably more work than I can manage with my tight deadline right now but I think I like it more than my current architecture. 
//It's also not really re-entrant, so I'd need to look at the pros and cons there.
class DecoratorTask : public Task {
public:
	DecoratorTask(int i_id, Task* child);

	Status run(Tick* t);

	virtual Status runChild(Tick* t, Task* childTask);
};