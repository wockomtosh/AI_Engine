#pragma once

class DecisionTreeNode {
public:
	virtual DecisionTreeNode* makeDecision() = 0;
};