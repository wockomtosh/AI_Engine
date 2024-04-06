#include "Blackboard.h"

float Blackboard::getFloat(std::string name)
{
	if (floatData.find(name) != floatData.end())
	{
		return floatData[name];
	}
	else
		return 0;
}

bool Blackboard::getBool(std::string name)
{
	if (boolData.find(name) != boolData.end())
	{
		return boolData[name];
	}
	return false;
}

Vector2 Blackboard::getVector(std::string name)
{
	if (vectorData.find(name) != vectorData.end())
	{
		return vectorData[name];
	}
	return Vector2();
}

void* Blackboard::getGeneric(std::string name)
{
	if (genericData.find(name) != genericData.end())
	{
		return genericData[name];
	}
	return nullptr;
}

void Blackboard::setFloat(std::string name, float value)
{
	floatData[name] = value;
}

void Blackboard::setBool(std::string name, bool value)
{
	boolData[name] = value;
}

void Blackboard::setVector(std::string name, Vector2 value)
{
	vectorData[name] = value;
}

void Blackboard::setGeneric(std::string name, void* value)
{
	genericData[name] = value;
}
