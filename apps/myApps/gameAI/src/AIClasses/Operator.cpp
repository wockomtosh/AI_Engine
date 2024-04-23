#include "Operator.h"

BitArray* Operator::applyOperator(BitArray* gameState) 
{
	if ((*gameState & *preconditions) == *preconditions)
	{
		//Delete first (gameState AND NOT deletedEffects)
		BitArray* deletedState;
		if (deletedEffects != nullptr)
		{
			deletedState = new BitArray(*gameState & ~*deletedEffects);
		}
		else
		{
			deletedState = new BitArray(*gameState);
		}

		//Then add (state OR addedEffects)
		BitArray* addedState;
		if (addedEffects != nullptr)
		{
			addedState = new BitArray(*deletedState | *addedEffects);
		}
		else
		{
			addedState = new BitArray(*deletedState);
		}
		return addedState;
	}
	//If the preconditions aren't met, we don't make any changes
	//To make the check easy we'll just return nullptr
	return nullptr;
}

Status Operator::execute(BitArray* gameState, std::shared_ptr<Action>& returnAction)
{
	//If our operator is not running, we want to send out the action and start it to running
	if (status == Status::none)
	{
		returnAction = action;
		status = Status::running;
	}

	//If the operator is running or just sent out an action, we need to check if that action is complete.
	//If that action is complete then we reset the operator to be used again in the future.
	//If not, and the action isn't interrupted, then we need to just let it do its thing.
	if (status == Status::running)
	{

		if (action->isComplete())
		{
			//The status of the operator should either be running or none, but we need to return a success or failure when it finishes
			Status returnStatus = action->isSuccessful() ? Status::success : Status::failure;
			action->reset();
			status = Status::none;
			return returnStatus;
		}

		//Check if the action was interrupted (no longer being tracked by the ActionManager) (see ActionTask)
		if (action.use_count() <= 1)
		{
			action->reset();
			status = Status::none;
			return Status::failure;
		}
	}

	return status;
}
