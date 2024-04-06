#include "ActionNode.h"

ActionNode::ActionNode(Action* action) :
	action(action) {}

DecisionTreeNode* ActionNode::makeDecision()
{
	return this;
}

Action* ActionNode::getAction()
{
	return this->action;
}
