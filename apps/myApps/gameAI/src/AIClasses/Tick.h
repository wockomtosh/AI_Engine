#pragma once
#include <vector>
#include <memory>
#include "Blackboard.h"
#include "Action.h"

enum Status { success, failure, running, error, none };

struct Task;

struct Tick {
	Status currentStatus = Status::none;
	Blackboard* blackboard;
	std::shared_ptr<Action> action;

	//Use these to support re-entrant behavior
	void open(Task* t); //Call when visiting a task for the first time
	void enter(Task* t); //Call when entering into a task
	void execute(Task* t); //Call when executing a task
	void exit(Task* t); //Call when leaving a task
	void close(Task* t); //Call when leaving a task for the last time
};