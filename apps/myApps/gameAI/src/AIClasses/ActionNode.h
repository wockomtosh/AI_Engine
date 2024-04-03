#pragma once
#include "DecisionTreeNode.h"
#include "Action.h"

class ActionNode : public DecisionTreeNode {
	Action* action;

public:
	ActionNode(Action* action);

	DecisionTreeNode* makeDecision();

	Action* getAction();
};