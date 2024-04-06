#pragma once
#include <vector>
#include <functional>
#include "Action.h"

//Careful not to flood the ActionManager
//This will be implemented as if each NPC has its own ActionManager
class ActionManager {
public:
	ActionManager() {}

	void scheduleAction(Action* action);
	void update(float dt);

private:
	std::vector<Action*> pending;
	std::vector<Action*> active;

	//increase queued time
	void updateActionQueuedTime(float dt);
	//Check if we have any interrupts on the queue
	void checkInterrupts();
	//Check priority and add things to actions
	void promoteQueuedToActive();
	//Execute active actions and remove completed actions
	void runActive();
};