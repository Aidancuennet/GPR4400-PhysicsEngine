#include "CircleMRUA.h"


namespace gpr4400
{
	bool CircleMRUA::operator==(CircleMRUA c)
	{
		return (center == c.center && radius == c.radius);
	}

	Vector2f CircleMRUA::GetPositionAtTime(float time) const
	{
		return center + velocity * time;
	}
