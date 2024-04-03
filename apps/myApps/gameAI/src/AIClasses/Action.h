#pragma once

struct Action {
	float priority;
	float queuedTime;
	float expiryTime;
	virtual bool canInterrupt() = 0;
	virtual bool canDoBoth(Action other) = 0;
	virtual bool isComplete() = 0;
	virtual void execute() = 0;
};