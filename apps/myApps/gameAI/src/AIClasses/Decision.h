#pragma once

//An abstract class to be implemented and passed into DecisionNodes
//I probably need to upgrade to smart pointers for Decisions
class Decision {

public:
	virtual bool isTrue() { return true; };
};