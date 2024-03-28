#pragma once
#include "Heuristic.h"

class DijkstraHeuristic : public Heuristic {
public:
	float estimate(int nodeID) { return 0; }
};