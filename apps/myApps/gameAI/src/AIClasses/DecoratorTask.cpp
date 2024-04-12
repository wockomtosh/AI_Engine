#include "DecoratorTask.h"

DecoratorTask::DecoratorTask(int i_id, Task* child)
{
	id = i_id;
	children.push_back(child);
}

//EXAMPLE OPTIONS: Until fail, delay, cooldown, retry until successful (n attempts), repeat (n times), inverter
Status DecoratorTask::run(Tick* t)
{
	if (status == Status::none)
	{
		t->open(this);
	}
	t->enter(this);
	t->execute(this);

	status = runChild(t, children[0]);

	t->exit(this);
	if (status != Status::running)
	{
		t->close(this);
	}
	return status;
}

Status DecoratorTask::runChild(Tick* t, Task* childTask)
{
	return childTask->run(t);
}
