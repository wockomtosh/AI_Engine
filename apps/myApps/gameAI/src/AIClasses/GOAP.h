#pragma once
#include <vector>
#include <string>

#include "../DataTypes/BitArray.h"
#include "Operator.h"
#include "Action.h"

struct StateRecord {
	BitArray* stateBits;
	std::vector<Operator*> planSoFar;
	float costSoFar;

	StateRecord() : 
		stateBits(nullptr), planSoFar(std::vector<Operator*>()), costSoFar(-1) {}
	StateRecord(BitArray* stateBits, std::vector<Operator*> planSoFar, float costSoFar) :
		stateBits(stateBits), planSoFar(planSoFar), costSoFar(costSoFar) {}
	StateRecord(const StateRecord& other) :
		stateBits(other.stateBits), planSoFar(other.planSoFar), costSoFar(other.costSoFar) {}

	//used for std::push_heap and related functions
	bool operator()(const StateRecord& a, const StateRecord& b);
	//The compiler got mad at me so I have to define this now
	bool operator==(const StateRecord& other) const;
};

class GOAP {
	BitArray* gameState;
	BitArray* goalState;
	std::vector<Operator*> operators;
	std::vector<Operator*> plan;
	int planIndex = 0;

public:
	GOAP(BitArray* gameState, BitArray* goalState, std::vector<Operator*> operators);

	void makePlan();
	std::shared_ptr<Action> followPlan();
	void setNewGoal(BitArray* newGoalState);
};