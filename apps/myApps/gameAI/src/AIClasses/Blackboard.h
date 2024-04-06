#pragma once
#include <map>
#include <string>
#include "../DataTypes/Vector2.h"

//This will hold a few maps for certain simple data types and then one for generic
class Blackboard {
	std::map<std::string, void*> genericData;
	std::map<std::string, float> floatData;
	std::map<std::string, bool> boolData;
	std::map<std::string, Vector2> vectorData;

public:
	Blackboard() {}

	float getFloat(std::string name);
	bool getBool(std::string name);
	Vector2 getVector(std::string name);
	void* getGeneric(std::string name);

	void setFloat(std::string name, float value);
	void setBool(std::string name, bool value);
	void setVector(std::string name, Vector2 value);
	void setGeneric(std::string name, void* value);
};