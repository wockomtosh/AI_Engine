#pragma once
#include "DecisionTreeNode.h"
#include "Action.h"
#include <memory>

class ActionNode : public DecisionTreeNode {
	std::shared_ptr<Action> action;

public:
	ActionNode(std::shared_ptr<Action> action);

	DecisionTreeNode* makeDecision();

	std::shared_ptr<Action> getAction();
};