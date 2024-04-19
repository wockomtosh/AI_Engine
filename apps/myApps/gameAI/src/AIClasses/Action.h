#pragma once
#include <string>

struct Action {
	int priority = 0;
	float queuedTime = 0;
	float expiryTime = 1;

	//I could add execution time to sort of pass in a dt to whatever needs it (though at that point it may be easier to refactor execute())
	//But also execution time could be set to -1 when it's removed. But again, maybe we just add a bool. 
	//If I don't want to refactor those are options.
	
	//Actions with a type of "" will not be scheduled
	std::string type = "";
	virtual bool canInterrupt() { return false; };
	//By default we can do two actions at the same time. We'll see if we need to change that later.
	virtual bool canDoBoth(Action* other) { return true; };
	virtual bool isComplete() { return true; }
	virtual bool isSuccessful() { return isComplete() ? true : false; }
	virtual void execute() {}
	//Used for continuous actions to let them start over
	virtual void reset() {}

	bool operator<(Action& other) {
		return priority < other.priority;
	}
	bool operator>(Action& other) {
		return priority > other.priority;
	}
};