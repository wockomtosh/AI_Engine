#pragma once
#include "DecisionTreeNode.h"
#include "Decision.h"

class DecisionNode : public DecisionTreeNode {
	DecisionTreeNode* left;
	DecisionTreeNode* right;
	Decision* decision;

public:
	DecisionNode(DecisionTreeNode* left, DecisionTreeNode* right, Decision* decision);
	
	DecisionTreeNode* makeDecision();
};