#pragma once
#include <memory>
#include "Action.h"
#include "Blackboard.h"
#include "Tick.h"
#include "Task.h"

class BehaviorTree {
	Task* root;
	Blackboard* blackboard;

public:
	BehaviorTree(Task* root, Blackboard* blackboard) :
		root(root), blackboard(blackboard) {}

	std::shared_ptr<Action> makeDecision();
};