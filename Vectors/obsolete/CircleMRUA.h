#pragma once

#include "vector2.h"
#include "Rigidbody.h"
#include <SFML/Graphics.hpp>


namespace gpr4400
{
	struct CircleMRUA : public Circle {
		bool operator==(CircleMRUA c);
		CircleMRUA()
		{
			static int seed = 0;
			srand(seed++);
			color = sf::Color(rand() % 255, rand() % 255, rand() % 255);
		}

		Vector2f GetPositionAtTime(float time) const;
		Vector2f velocity = { 0.f, 0.f };
		const Vector2f G = { 0.f, 9.81f }; // G (9.81 m/s^2)
		const float R = 0.90f;
		float mass;
		void UpdateVariable(double delta_time, int dx, int dy);
		sf::Color color;
}
