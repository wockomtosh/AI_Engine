#include "ActionTask.h"

ActionTask::ActionTask(int i_id, std::shared_ptr<Action> i_action) :
	action(i_action)
{
	id = i_id;
}

Status ActionTask::run(Tick* t)
{
	if (status == Status::none)
	{
		t->open(this);

		t->action = action;
		status = Status::running;
	}

	if (status == Status::running)
	{
		t->enter(this);
		t->execute(this);

		//TODO: I need a solution for resetting my action
		//In the action manager it executes and then checks for completion
		//Here it checks for completion first, so we need to make sure that we have a way to reset it.
		//For now I'm adding a reset() function, but it feels sloppy
		if (action->isComplete())
		{
			t->exit(this);
			t->close(this);
			status = action->isSuccessful() ? Status::success : Status::failure;
			action->reset(); //reset after success check to make sure we don't change important info
			return status;
		}

		//Check if the action was interrupted (no longer being tracked by the ActionManager)
		//For now I'm going to count this as a failure, though it could be revised.
		//TODO: This is sort of a hack, and I don't know if it's reliable
		//Also, in my current implementation I think the BT only has one action manager, so things probably shouldn't really get interrupted much.
		if (action.use_count() <= 1)
		{
			t->exit(this);
			t->close(this);
			status = Status::failure;
			return status;
		}
	}

	//If we're still running we don't need to give a new action to the tick, just keep running the old one.
	t->exit(this);
	return status;
}



//WACK IDEA BELOW

//template<class T>
//ActionTask<T>::ActionTask(int i_id, T i_actionType) :
//	actionType(i_actionType), currentAction(nullptr)
//{
//	id = i_id;
//	status = Status::none;
//}

//template<class T>
//Status ActionTask<T>::run(Tick* t)
//{
//	//TODO: figure out how this works with tick->open. Do we set the status here or in the tick? Do we call open here?
//	if (status == Status::none)
//	{
//		//Does this work? How do I pass information into the constructor?
//		std::shared_ptr<Action> newAction(new T());
//		t->action = newAction;
//		currentAction = newAction;
//		status = Status::running;
//		return status;
//	}
//	if (status == Status::running)
//	{
//		if (action->isComplete())
//		{
//			currentAction = nullptr;
//			//TODO Later: Have some sort of success check
//			return Status::success;
//
//		}
//	}
//
//	return Status::failure;
//}

