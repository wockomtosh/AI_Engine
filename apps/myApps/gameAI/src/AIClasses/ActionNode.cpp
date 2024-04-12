#include "ActionNode.h"

ActionNode::ActionNode(std::shared_ptr<Action> action) :
	action(action) {}

DecisionTreeNode* ActionNode::makeDecision()
{
	return this;
}

std::shared_ptr<Action> ActionNode::getAction()
{
	return this->action;
}
