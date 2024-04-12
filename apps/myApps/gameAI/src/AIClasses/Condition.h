#pragma once
#include "Blackboard.h"

//Like Decisions but takes in a blackboard in the isTrue function, since in BTs we expect to have access to some data like that.
class Condition {

public:
	virtual bool isTrue(Blackboard* blackboard) { return true; }
};