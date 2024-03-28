#pragma once

//Most derived heuristics should probably take in the graph as a private member to use in the estimate function. And probably also the goal.
class Heuristic {
public:
	virtual float estimate(int nodeID) = 0;
};