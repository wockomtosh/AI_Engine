#pragma once

//An abstract class to be implemented and passed into DecisionNodes
class Decision {

public:
	virtual bool isTrue() = 0;
};