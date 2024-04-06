#include "DecisionNode.h"

DecisionNode::DecisionNode(DecisionTreeNode* left, DecisionTreeNode* right, Decision* decision) :
	left(left), right(right), decision(decision) {}

DecisionTreeNode* DecisionNode::makeDecision()
{
	if (decision->isTrue())
	{
		return left->makeDecision();
	}
	return right->makeDecision();
}
