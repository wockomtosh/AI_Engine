#pragma once

namespace Orientation {
	inline float clampOrientation(float i_orientation)
	{
		//I'm using degrees
		if (i_orientation < 0)
		{
			i_orientation += 360;
		}
		else if (i_orientation > 360)
		{
			i_orientation -= 360;
		}

		return i_orientation;
	}
}