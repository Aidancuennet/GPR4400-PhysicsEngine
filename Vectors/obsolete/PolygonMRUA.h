#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Circle.h"

namespace gpr4400
{
	struct PolygonMRUA : public Circle
	{
		bool operator==(PolygonMRUA c);
		PolygonMRUA(Vector2f velo, std::vector<Vector2f>& points);
		Vector2f GetPositionAtTime(float time) const;
		Vector2f GetPrintingCenter() const;
		float GetRadiusInMeters() const;
		Vector2f velocity = { 0.f, 0.f };
		const Vector2f G = { 0.f, 0.f }; // G (9.81 m/s^2)
		const float R = 0.90f;
		float mass = 10.f;
		void UpdateVariable(double delta_time, int dx, int dy);
		sf::Color color = sf::Color().Red;
		std::vector<Vector2f> points_ = {};


	protected:
		// Just bouncing the borders.
		void CorrectVelocity(int dx, int dy);

		void CorrectPosition(int dx, int dy);

	private:
		double printing_m_ = 100.0;
		Vector2f printing_center_;

	};
}
