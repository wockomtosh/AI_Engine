#include "ActionManager.h"
#include <algorithm>

//TODO: probably eventually make my own priority queue so I can have it how I'd like. Or split these out into a util file.
//Wrapper for std::push_heap
void heapPush(std::vector<std::shared_ptr<Action>>& list, std::shared_ptr<Action> value)
{
	list.push_back(value);
	std::push_heap(list.begin(), list.end());
}

//Wrapper for std::pop_heap
std::shared_ptr<Action> heapPop(std::vector<std::shared_ptr<Action>>& list)
{
	std::pop_heap(list.begin(), list.end());
	std::shared_ptr<Action> returnValue = list.back();
	list.pop_back();

	return returnValue;
}

//Wrapper for std::make_heap
void makeHeap(std::vector<std::shared_ptr<Action>>& list)
{
	std::make_heap(list.begin(), list.end());
}

void ActionManager::scheduleAction(std::shared_ptr<Action> action)
{
	//Don't schedule empty actions
	if (action->type != "")
	{
		action->queuedTime = 0;
		heapPush(pending, action);
	}
}

void ActionManager::update(float dt)
{
	updateActionQueuedTime(dt);
	checkInterrupts();
	promoteQueuedToActive();
	runActive();
}

void ActionManager::updateActionQueuedTime(float dt)
{
	for (int i = 0; i < pending.size(); i++)
	{
		pending[i]->queuedTime += dt;
	}
}

//Having this separate from our promote function lets us put interrupts on the queue and then promote whatever can be done alongside them
void ActionManager::checkInterrupts()
{
	float activeHighestPriority = 0;
	if (active.size() > 0)
	{
		activeHighestPriority = active[0]->priority;
	}
	
	//Interrupts apply if they are higher priority than all the active actions. 
	//There are issues with this type of loop since it doesn't happen in priority order, but I'll worry about that later.
	for (auto i = pending.begin(); i != pending.end(); )
	{
		std::shared_ptr<Action> action = *i;
		if (action->canInterrupt())
		{
			if (action->priority >= activeHighestPriority)
			{
				i = pending.erase(i);
				active.clear();
				active.push_back(action);
				//Don't forget to set our new highest priority
				activeHighestPriority = action->priority;
				//Continue so we don't increment, erase() already moves us forward
				continue;
			}
		}
		++i;
	}
	makeHeap(pending);
}

void ActionManager::promoteQueuedToActive()
{
	//To iterate we're popping everything off of pending. If it isn't being promoted it's put back onto pendingCopy
	std::vector<std::shared_ptr<Action>> pendingCopy;
	int numPending = pending.size();
	for (int i = 0; i < numPending; i++)
	{
		std::shared_ptr<Action> curAction = heapPop(pending);
		if (curAction->queuedTime > curAction->expiryTime)
		{
			continue;
		}

		bool canPromote = true;
		for (std::shared_ptr<Action> activeAction : active)
		{
			if (!curAction->canDoBoth(activeAction.get()))
			{
				canPromote = false;
				break;
			}
		}
		if (canPromote)
		{
			heapPush(active, curAction);
		}
		else
		{
			//If it isn't being promoted then put it back on pending
			heapPush(pendingCopy, curAction);
		}
	}
	//Pending should be empty now, set it to our copy.
	pending = pendingCopy;
}

// https://stackoverflow.com/questions/10360461/removing-item-from-vector-while-in-c11-range-for-loop
// https://www.reddit.com/r/Cplusplus/comments/twsimo/erase_an_element_from_a_vector_using_a_range_for/
void ActionManager::runActive()
{
	//A special kind of for loop that lets me conditionally erase things.
	for (auto i = active.begin(); i != active.end(); )
	{
		std::shared_ptr<Action> action = *i;
		action->execute();
		if (action->isComplete())
		{
			//I converted to shared pointers specifically for this part so we can delete the action here
			//But other places that still need it (especially Behavior Trees) can still have it
			i = active.erase(i);
		}
		else
		{
			++i;
		}
	}
	makeHeap(active);
}
