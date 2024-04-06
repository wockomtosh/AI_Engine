#pragma once
#include <string>
#include "../Components/Rigidbody.h"

class ISteeringBehavior {
public:
	virtual ~ISteeringBehavior() {}
	//To pass in the necessary parameters we can pass them into the constructor of the derived class
	//Many of our steering functions will require different data, so this will allow us to be flexible with that and 
	//still use an interface.
	virtual Acceleration getSteering() = 0; 

	virtual std::string getName() { return ""; }
};