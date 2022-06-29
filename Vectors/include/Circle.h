#pragma once
#include "vector2.h"

namespace gpr4400
{
	struct Circle
	{
		Vector2f center;
		float radius;
	};

	bool Intersect(Circle c1, Circle c2);
}