#pragma once

struct DirectedWeightedEdge {
	float weight;
	int source;
	int sink;

	DirectedWeightedEdge() :
		weight(0), source(0), sink(0)
	{}

	DirectedWeightedEdge(float weight, int source, int sink) :
		weight(weight), source(source), sink(sink)
	{}

	bool operator==(DirectedWeightedEdge other)
	{
		return weight == other.weight && source == other.source && sink == other.sink;
	}

	static DirectedWeightedEdge NULL_EDGE;
};

DirectedWeightedEdge DirectedWeightedEdge::NULL_EDGE = DirectedWeightedEdge(-1, -1, -1);