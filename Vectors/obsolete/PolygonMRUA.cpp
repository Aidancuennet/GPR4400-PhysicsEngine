#include "PolygonMRUA.h"

namespace gpr4400
{

	bool PolygonMRUA::operator==(PolygonMRUA c)
	{
		return (center == c.center && radius == c.radius);
	}

	PolygonMRUA::PolygonMRUA(Vector2f velo, std::vector<Vector2f>& points)
	{
		points_ = points;
		velocity = velo;
		center = { 0, 0 };
		for (auto& point : points_)
		{
			center = center + point;
		}
		center.x = center.x / points_.size();
		center.y = center.y / points_.size();
		printing_center_ = center * printing_m_;
		radius = 0.f;
		for (auto& point : points_)
		{
			float temp = (center - point).Length();
			if (temp > radius)
			{
				radius = temp;
			}
		}
		for (auto& point : points_)
		{
			point = point - center;
		}
	}

	Vector2f PolygonMRUA::GetPositionAtTime(float time) const
	{
		return center + velocity * time;
	}

	Vector2f PolygonMRUA::GetPrintingCenter() const
	{
		return printing_center_;
	}

	float PolygonMRUA::GetRadiusInMeters() const
	{
		return radius / printing_m_;
	}

	void PolygonMRUA::UpdateVariable(double delta_time, int dx, int dy)
	{
		Vector2f previous_center = center;
		center =
			0.5 * G * delta_time * delta_time + // 1/2*G*t^2
			velocity * delta_time // + v0*t
			+ center; // + x0
		// delta x / delta t.
		velocity = (center - previous_center) * 1.0f / delta_time;
		printing_center_ = center * printing_m_;
		CorrectPosition(dx, dy);
		CorrectVelocity(dx, dy);
		center = printing_center_ * 1 / printing_m_;
	}
	void PolygonMRUA::CorrectVelocity(int dx, int dy)
	{
		if (printing_center_.x <= 0 + radius * 100)
			velocity.x = -R * velocity.x;
		if (printing_center_.y <= 0 + radius * 100)
			velocity.y = -R * velocity.y;
		if (printing_center_.x >= (dx - radius * 100))
			velocity.x = -R * velocity.x;
		if (printing_center_.y >= (dy - radius * 100))
			velocity.y = -R * velocity.y;
	}
	void PolygonMRUA::CorrectPosition(int dx, int dy)
	{
		Vector2f previous_center = printing_center_;
		if (printing_center_.x <= 0 + radius * 100)
			printing_center_.x = radius * 100;
		if (printing_center_.y <= 0 + radius * 100)
			printing_center_.y = radius * 100;
		if (printing_center_.x >= (dx - radius * 100))
			printing_center_.x = dx - radius * 100;
		if (printing_center_.y >= (dy - radius * 100))
			printing_center_.y = dy - radius * 100;
	}
}