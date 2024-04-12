#pragma once
#include <vector>
#include <functional>
#include "Action.h"
#include <memory>

//Careful not to flood the ActionManager
//This will be implemented as if each NPC has its own ActionManager
class ActionManager {
public:
	ActionManager() {}

	void scheduleAction(std::shared_ptr<Action> action);
	void update(float dt);

private:
	std::vector<std::shared_ptr<Action>> pending;
	std::vector<std::shared_ptr<Action>> active;

	//increase queued time
	void updateActionQueuedTime(float dt);
	//Check if we have any interrupts on the queue
	void checkInterrupts();
	//Check priority and add things to actions
	void promoteQueuedToActive();
	//Execute active actions and remove completed actions
	void runActive();
};