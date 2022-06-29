#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "vector2.h"
#include "Rigidbody.h"
#include <cmath>

namespace gpr4400 {

	constexpr float epsilon = 1e-4f;

	inline std::ostream& operator<<(std::ostream& os, Vector2f vec) {
		os << "{ " << vec.x << ", " << vec.y << " }";
		return os;
	}

	Vector2f ComputeNormal(Vector2f center, Vector2f i)
	{
		return(i - center).Normalize();
	}
	Vector2f ComputeTangent(Vector2f center, Vector2f i)
	{
		const Vector2f tangent = ComputeNormal(center, i);
		return { tangent.y, -tangent.x };
	}

	struct CircleMRUA : public Circle {
		bool operator==(CircleMRUA c)
		{
			return(center == c.center && radius == c.radius);
		}
		Vector2f get_position_at_time(float time) const
		{
			return center + velocity * time;
		}
		Vector2f velocity = { 0.f, 0.f };
		const Vector2f G = { 0.f, 0.f }; // G (9.81 m/s^2)
		const float R = 0.90f;
		float mass;
		void update_variable(double delta_time, int dx, int dy) {
			Vector2f previous_center = center;
			center =
				0.5 * G * delta_time * delta_time + // 1/2*G*t^2
				velocity * delta_time				// + v0*t
				+ center;							// + x0
			// delta x / delta t.
			velocity = (center - previous_center) * 1.0f / delta_time;
			printing_center_ = center * printing_m_;
			correct_position(dx, dy);
			correct_velocity(dx, dy);
			center = printing_center_ * 1 / printing_m_;
		}
		Vector2f get_printing_center() const { return printing_center_; }
		float get_radius_in_meters() const { return radius / printing_m_; }
		sf::Color color = sf::Color(rand() % 255, rand() % 255, rand() % 255);

	protected:
		// Just bouncing the borders.
		void correct_velocity(int dx, int dy) {
			if (printing_center_.x <= 0 + radius)
				velocity.x = -R * velocity.x;
			if (printing_center_.y <= 0 + radius)
				velocity.y = -R * velocity.y;
			if (printing_center_.x >= (dx - radius))
				velocity.x = -R * velocity.x;
			if (printing_center_.y >= (dy - radius))
				velocity.y = -R * velocity.y;
		}
		void correct_position(int dx, int dy) {
			Vector2f previous_center = printing_center_;
			if (printing_center_.x <= 0 + radius)
				printing_center_.x = radius;
			if (printing_center_.y <= 0 + radius)
				printing_center_.y = radius;
			if (printing_center_.x >= (dx - radius))
				printing_center_.x = dx - radius;
			if (printing_center_.y >= (dy - radius))
				printing_center_.y = dy - radius;
		}

	private:
		double printing_m_ = 100.0;
		Vector2f printing_center_ = center * printing_m_;

	};


	class PhysicMRUA {
	public:
		PhysicMRUA(int dx, int dy) : dx_(dx), dy_(dy) {}
		void Init() {
			circles_.clear();
		}

		void CreateCircle(Vector2f location, float radius, Vector2f velocity0, float mass)
		{
			CircleMRUA circle;
			circle.center = location;
			circle.radius = radius;
			circle.velocity = velocity0;
			circle.mass = mass;

			circles_.push_back(circle);
		}
		void UpdateDrawData(double delta_time) {
			float new_time = delta_time * 1.0;
			for (auto& circle : circles_) {
				circle.update_variable(new_time, dx_, dy_);
			}
			Simulate(new_time);
		}
		void ResolveIntersect(CircleMRUA& c1, CircleMRUA& c2)
		{
			std::cout << "Intersect!" << std::endl;
			//During impact
			float v1n = ComputeNormal(c1.center, ContactPoint(c1, c2)).x * c1.velocity.x + ComputeNormal(
				c1.center, ContactPoint(c1, c2)).y * c1.velocity.y;
			float v1g = ComputeTangent(c1.center, ContactPoint(c1, c2)).x * c1.velocity.x + ComputeTangent(
				c1.center, ContactPoint(c1, c2)).y * c1.velocity.y;
			float v2n = ComputeNormal(c2.center, ContactPoint(c1, c2)).x * c2.velocity.x + ComputeNormal(
				c2.center, ContactPoint(c1, c2)).y * c2.velocity.y;
			float v2g = ComputeTangent(c2.center, ContactPoint(c1, c2)).x * c2.velocity.x + ComputeTangent(
				c2.center, ContactPoint(c1, c2)).y * c2.velocity.y;

			//After impact
			c1.velocity.x = ComputeNormal(c1.center, ContactPoint(c1, c2)).x * v2n + ComputeTangent(
				c1.center, ContactPoint(c1, c2)).x * v1g * -c1.R;
			c1.velocity.y = ComputeNormal(c1.center, ContactPoint(c1, c2)).y * v2n + ComputeTangent(
				c1.center, ContactPoint(c1, c2)).y * v1g * -c1.R;
			c2.velocity.x = ComputeNormal(c2.center, ContactPoint(c1, c2)).x * v1n + ComputeTangent(
				c2.center, ContactPoint(c1, c2)).x * v2g * -c2.R;
			c2.velocity.y = ComputeNormal(c2.center, ContactPoint(c1, c2)).y * v1n + ComputeTangent(
				c2.center, ContactPoint(c1, c2)).y * v2g * -c2.R;

			if (Intersect(c1, c2))
			{
				c1.center = RelocateCenter(c1, ContactPoint(c1, c2));
				c2.center = RelocateCenter(c2, ContactPoint(c1, c2));
				c1.velocity = c1.velocity * -c1.R;
				c2.velocity = c2.velocity * -c2.R;
			}
		}
		bool Intersect(const CircleMRUA& m1, const CircleMRUA& m2)
		{
			return CalculateDistance(m1.center, m2.center) <= (m1.get_radius_in_meters() + m2.get_radius_in_meters());
		}
		Vector2f ContactPoint(const CircleMRUA& c1, const CircleMRUA& c2)
		{
			double ratio = c1.get_radius_in_meters() / (c1.get_radius_in_meters() + c2.get_radius_in_meters());
			return(c2.center - c1.center) * ratio + c1.center;
		}
		Vector2f RelocateCenter(const CircleMRUA& c1, const Vector2f& I)
		{
			double ratio = c1.get_radius_in_meters() * 1.1 / (c1.center - I).Length();
			return (c1.center - I) * ratio + I;
		}

		void Simulate(float delta_time)
		{
			for (auto& body : circles_)
			{
				body.center = body.get_position_at_time(delta_time);
				for (auto& bodyCheck : circles_)
				{
					if (body == bodyCheck)
					{
						continue;
					}
					if (Intersect(body, bodyCheck))
					{
						ResolveIntersect(body, bodyCheck);
					}
				}
			}
		}

	protected:
		int dx_ = 1280;
		int dy_ = 720;
		std::vector<CircleMRUA> circles_;
	};




} // End namespace gpr4400.