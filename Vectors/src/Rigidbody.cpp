#include "Rigidbody.h"
#include <algorithm>

namespace gpr4400
{
	Vector2f Rigidbody::GetPositionAtTime(float time) const
	{
		return center + velocity * time;
	}

	bool Rigidbody::operator==(Rigidbody rb)
	{
		return(center == rb.center && radius == rb.radius);
	}

	Vector2f ResolveIntersect(Rigidbody& rb1, Rigidbody& rb2)
	{
		Vector2f inter;
		float ratio = rb1.radius / (rb1.radius + rb2.radius);
		inter.x = rb1.center.x * ratio;
		inter.y = rb1.center.y * ratio;
		return inter;
	}

	std::vector<Rigidbody> Simulate(std::vector<Rigidbody>& rb, float time)
	{
		std::vector<Rigidbody> nvrb;
		for (auto& body : rb)
		{
			body.center = body.GetPositionAtTime(time);
			for (auto& bodyCheck : rb)
			{
				if (body == bodyCheck)
				{
					continue;
				}
				if (Intersect(body, bodyCheck))
				{
					ResolveIntersect(body, bodyCheck);
					if (std::find(nvrb.begin(), nvrb.end(), body) == nvrb.end()) {
						nvrb.push_back(body);
					}
					if (std::find(nvrb.begin(), nvrb.end(), bodyCheck) == nvrb.end()) {
						nvrb.push_back(bodyCheck);
					}
				}

			}
		}
		return nvrb;
	}
}

