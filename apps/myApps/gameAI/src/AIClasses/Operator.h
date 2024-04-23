#pragma once
#include <string>
#include <memory>

#include "../DataTypes/BitArray.h"
#include "../DataTypes/Status.h"
#include "Action.h"

//If I were to do this again I'd want to try using functions for preconditions/effects to give more flexibility in how those conditions are checked
class Operator {
	std::string name;
	std::shared_ptr<Action> action;
	BitArray* preconditions;
	BitArray* addedEffects;
	BitArray* deletedEffects;
	float cost;
	Status status = Status::none;

public:
	Operator() :
		name(""), action(nullptr), preconditions(nullptr), addedEffects(nullptr), deletedEffects(nullptr), cost(1) {}

	Operator(std::string name, std::shared_ptr<Action> action) :
		name(name), action(action), preconditions(nullptr), addedEffects(nullptr), deletedEffects(nullptr), cost(1) {}

	Operator(std::string name, std::shared_ptr<Action> action, BitArray* preconditions, BitArray* addedEffects = nullptr, BitArray* deletedEffects = nullptr, float cost = 1) :
		name(name), action(action), preconditions(preconditions), addedEffects(addedEffects), deletedEffects(deletedEffects), cost(cost) {}

	//Certain things like a Move operator might want to override this, but for now I'm ignoring that.
	//A move operator could override this to make it just take the next step in a path,
	//And if no path is available, find a path.
	BitArray* applyOperator(BitArray* gameState);

	//We can do a generic execute, but it might also just be easier to do a custom execute for each type
	//For now I'll go generic and see if a use case pops up later.
	Status execute(BitArray* gameState, std::shared_ptr<Action>& returnAction);

	float getCost() { return cost; }

	std::string getName() { return name; }
};