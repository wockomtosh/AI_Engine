#include "GOAP.h"
#include <algorithm>

StateRecord findInListByNode(std::vector<StateRecord> list, BitArray* bits)
{
	for (StateRecord state : list)
	{
		if (*state.stateBits == *bits)
		{
			return state;
		}
	}
	return StateRecord();
}

void heapPush(std::vector<StateRecord>& list, StateRecord value)
{
	list.push_back(value);
	std::push_heap(list.begin(), list.end(), StateRecord());
}

StateRecord heapPop(std::vector<StateRecord>& list)
{
	std::pop_heap(list.begin(), list.end(), StateRecord());
	StateRecord returnValue = list.back();
	list.pop_back();

	return returnValue;
}

GOAP::GOAP(BitArray* gameState, BitArray* goalState, std::vector<Operator*> operators) :
	gameState(gameState), goalState(goalState), operators(operators), plan(std::vector<Operator*>()) {}

void GOAP::makePlan()
{
	//Reset this for followPlan
	planIndex = 0;

	//Initialize fringe
	StateRecord startRecord = StateRecord(gameState, std::vector<Operator*>(), 0);
	std::vector<StateRecord> openList;
	heapPush(openList, startRecord);

	std::vector<StateRecord> closedList;

	StateRecord current;
	while (!openList.empty())
	{
		current = heapPop(openList);

		if (*current.stateBits == *goalState)
		{
			break;
		}

		//Generate unique children
		for (Operator* op : operators)
		{
			BitArray* newState = op->applyOperator(current.stateBits);
			if (newState == nullptr)
			{
				continue;
			}
			float newCost = current.costSoFar + op->getCost();

			StateRecord endStateRecord = findInListByNode(closedList, newState);
			if (endStateRecord.stateBits != nullptr)
			{
				if (endStateRecord.costSoFar <= newCost)
				{
					//Worse duplicate, skip it.
					continue;
				}
				else
				{
					//If it's a better duplicate, then erase the one in the closed list
					closedList.erase(std::find(closedList.begin(), closedList.end(), endStateRecord));
				}
			}

			endStateRecord = findInListByNode(openList, newState);
			if (endStateRecord.stateBits != nullptr)
			{
				if (endStateRecord.costSoFar <= newCost)
				{
					//Worse duplicate, skip it
					continue;
				}
				//Should I be erasing from the openList if we have a better option elsewhere?
				//When running through manually it seems that the algorithm still works, but we have to redo a bunch of nodes that we already did.
				//They get pruned here when they're redone, but we still generate them.
				//I think the tradeoff is whether or not it's more efficient to delete the state and have to resort the heap, or to just redo a few nodes.
				//Generating the plan at the end might get messed up because we could have duplicate nodes in the closed list.
			}

			//If it's unique or a better duplicate, we want to insert it.
			std::vector<Operator*> newPlan = current.planSoFar;
			newPlan.push_back(op);
			endStateRecord = StateRecord(newState, newPlan, newCost);
			heapPush(openList, endStateRecord);
		}

		closedList.push_back(current);
	}

	if (*current.stateBits == *goalState)
	{
		//I'm building the plan as I go this time because it's not trivial to work backwards from operators.
		//Some operators could do an undo, but others (like move) could be more complicated
		//Also I want to try both ways.
		plan = current.planSoFar;
	}
}

std::shared_ptr<Action> GOAP::followPlan()
{
	if (plan.size() > 0)
	{
		std::shared_ptr<Action> returnAction = nullptr;
		//Enact current operator
		Status status = plan[planIndex]->execute(gameState, returnAction);
		
		//If the current operator is running then we need to just let it run
		if (status == Status::running)
		{
			return returnAction;
		}
		
		//If the current operator is finished and successful move to the next one
		//For this to work the way I've set it up we need to be calling this frequently enough that we don't need to execute the new operator
		if (status == Status::success)
		{
			//We don't want it to go out of bounds when the last operator finishes
			if (planIndex < plan.size() - 1)
			{
				planIndex++;
			}
			return returnAction;
		}
		
		//If the current operator is finished and unsuccessful then we need to make a new plan
		if (status == Status::failure)
		{
			makePlan();
			return nullptr;
		}

		//If we've reached our goal then just leave the last operator to decide what to do
		//Later we could have a terminating operator (most would use StayStill, but maybe some others would do something else
	}
	else
	{
		//Maybe implement a failure count later to let this error out if it keeps trying too much
		makePlan();
	}

	return nullptr;
}

void GOAP::setNewGoal(BitArray* newGoalState)
{
	delete goalState;
	goalState = newGoalState;
	makePlan();
}

bool StateRecord::operator()(const StateRecord& a, const StateRecord& b)
{
	return a.costSoFar > b.costSoFar;
}

bool StateRecord::operator==(const StateRecord& other) const
{
	return *stateBits == *other.stateBits && planSoFar == other.planSoFar && costSoFar == other.costSoFar;
}
