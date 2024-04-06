#pragma once
#include "DecisionTreeNode.h"
#include "ActionNode.h"
#include "Action.h"
#include "Blackboard.h"

//Basically this is meant to hold the root of the tree (so it can retrieve an action) and an abstraction scheme (Blackboard for my uses)
class DecisionTree {
	DecisionTreeNode* root;
	Blackboard* blackboard;

public:
	DecisionTree(DecisionTreeNode* root/*, Blackboard* blackboard*/) :
		root(root)/*, blackboard(blackboard)*/ {}

	Action* makeDecision()
	{
		ActionNode* action = static_cast<ActionNode*>(root->makeDecision());
		return action->getAction();
	}
};