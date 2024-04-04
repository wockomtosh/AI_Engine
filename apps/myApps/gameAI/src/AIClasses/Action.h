#pragma once

struct Action {
	float priority;
	float queuedTime;
	float expiryTime;
	virtual bool canInterrupt() { return false; };
	//By default we can do two actions at the same time. We'll see if we need to change that later.
	virtual bool canDoBoth(Action other) { return true; };
	virtual bool isComplete() = 0;
	virtual void execute() = 0;
};