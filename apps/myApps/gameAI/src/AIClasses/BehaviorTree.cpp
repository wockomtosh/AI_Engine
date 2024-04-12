#include "BehaviorTree.h"

std::shared_ptr<Action> BehaviorTree::makeDecision()
{
	//INSERT MAGIC HERE?? Updating bb?
	Tick* t = new Tick();
	t->blackboard = blackboard;

	//INSERT MAGIC HERE Re-entrant behavior?

	root->run(t);
	
	//Reset the status of the root? Or does the status of the root not matter? 
	//I don't think it does, I think only child statuses matter, and the root handles that inside

	return t->action;
}
