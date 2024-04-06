#pragma once
#include <vector>
#include "ISteeringBehavior.h"
#include "../Components/AIComponent.h"
#include "Pathfinding/Graph/DirectedWeightedEdge.h"
#include "Pathfinding/Graph/TileGraph.h"
#include "DynamicArrive.h"
#include "DynamicAlign.h"

class DynamicPathfollow : public ISteeringBehavior {
	AIComponent* self;
	//TODO: ideally we should pass in a localization function rather than the whole tile graph
	TileGraph* graph;
	std::vector<DirectedWeightedEdge> path; 
	float sinkRadius;
	float targetRadius;
	float timeToTargetVelocity;
	//I'm omitting slow radius becasue in a normal tile graph I expect the tiles to be small and I don't want to be slowing down all the time

	int pathIndex = 0;


public:
	DynamicPathfollow(AIComponent* self, TileGraph* graph, std::vector<DirectedWeightedEdge> path, float sinkRadius = 16, float targetRadius = 10, float timeToTargetVelocity = .1);
	~DynamicPathfollow() {}
	Acceleration getSteering();
	std::string getName() { return "DynamicPathfollow"; }
};