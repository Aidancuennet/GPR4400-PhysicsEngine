#include "Circle.h"
#include <cmath>

namespace gpr4400
{

	bool Intersect(Circle c1, Circle c2)
	{
		return std::abs(CalculateDistance(c1.center, c2.center) < c1.radius + c2.radius);
	}

}