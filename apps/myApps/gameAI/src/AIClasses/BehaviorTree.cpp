#include "BehaviorTree.h"

std::shared_ptr<Action> BehaviorTree::makeDecision()
{
	Tick* t = new Tick();
	t->blackboard = blackboard;

	Status currentStatus = root->run(t);

	//TODO: Figure out how to get higher priority nodes to have their conditions checked without rerunning the entire tree each time...
	//Maybe I just have to rerun the whole tree to do that though
	if (currentStatus == Status::success || currentStatus == Status::failure)
	{
		t->close(root);
	}
	
	return t->action;
}
