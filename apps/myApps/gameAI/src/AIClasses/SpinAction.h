#pragma once
#include "Action.h"
#include "Blackboard.h"
#include "../Components/AIComponent.h"
#include "DynamicVelocityMatch.h"
#include "DynamicAlign.h"
#include "../DataTypes/Orientation.h"

class SpinAction : public Action {
	AIComponent* self;
	bool complete = false;
	bool entered = false;
	int spinIndex = 0;
	float startingOrientation = 0; //Becasue I construct the action at the beginning this needs to be set when we're starting

public:
	SpinAction(AIComponent* self) :
		self(self)
	{
		priority = 1;
		type = "movement";
	}

	bool canDoBoth(Action* other) { return other->type != "movement"; }

	bool isComplete() { return complete; }

	bool isOrientationCloseEnough(float current, float target)
	{
		return current < (target + 3) && current >(target - 3);
	}

	void execute()
	{
		//Reset/startup stuff
		if (spinIndex == 0 && !entered)
		{
			startingOrientation = self->body->orientation;
			entered = true;
			complete = false;
		}		

		if (!self->body->velocity.isWithinRangeOf(Vector2(), .1, .1))
		{
			delete self->behavior;
			self->behavior = new DynamicVelocityMatch(self, Vector2());
			return;
		}
		
		if (spinIndex < 3)
		{
			//We want to pick 3 places to rotate to to complete a rotation, so 120 degrees for each step
			float targetOrientation = Orientation::clampOrientation(startingOrientation + (120 * (spinIndex + 1)));

			if (isOrientationCloseEnough(self->body->orientation, targetOrientation))
			{
				spinIndex++;
				targetOrientation = startingOrientation + (120 * (spinIndex + 1));
			}
			delete self->behavior;
			self->behavior = new DynamicAlign(self, targetOrientation);
			return;
		}
		
		complete = true;
	}

	void reset()
	{
		complete = false;
		entered = false;
		spinIndex = 0;
	}
};