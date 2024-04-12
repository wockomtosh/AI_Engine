#pragma once
#include <string>

struct Action {
	int priority = 0;
	float queuedTime = 0;
	float expiryTime = 1;
	//Actions with a type of "" will not be scheduled
	std::string type = "";
	virtual bool canInterrupt() { return false; };
	//By default we can do two actions at the same time. We'll see if we need to change that later.
	virtual bool canDoBoth(Action* other) { return true; };
	virtual bool isComplete() { return true; }
	virtual void execute() {}

	bool operator<(Action& other) {
		return priority < other.priority;
	}
	bool operator>(Action& other) {
		return priority > other.priority;
	}
};