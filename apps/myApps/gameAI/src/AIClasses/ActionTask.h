#pragma once
#include "Task.h"
#include "Action.h"
#include <memory>

//template <class T>
class ActionTask : public Task {
	//T actionType;
	std::shared_ptr<Action> action;

public:
	ActionTask(int i_id, std::shared_ptr<Action> i_action);
	//ActionTask(int i_id, T i_actionType);

	Status run(Tick* t);
};