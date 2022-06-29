#pragma once
#include <vector>
#include "Circle.h"


namespace gpr4400
{
	struct Rigidbody : public Circle
	{
		float mass;
		Vector2f velocity;
		Vector2f GetPositionAtTime(float time) const;
		bool operator==(Rigidbody rb);
	};

	Vector2f ResolveIntersect(Rigidbody& rb1, Rigidbody& rb2);
	std::vector<Rigidbody> Simulate(std::vector<Rigidbody>& rb, float time);
}