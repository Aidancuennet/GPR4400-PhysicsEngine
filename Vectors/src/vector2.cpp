#include <vector2.h>
#include <cmath>

namespace gpr4400
{
	Vector2i Vector2i::operator+(Vector2i v) const
	{
		return Vector2i{ x + v.x, y + v.y };
	}

	Vector2i Vector2i::operator-(Vector2i v) const
	{
		return Vector2i{ x - v.x, y - v.y };
	}

	Vector2i Vector2i::operator*(int i) const
	{
		return Vector2i{ x * i, y * i };
	}

	Vector2i Vector2i::operator/(int i) const
	{
		return Vector2i{ x / i, y / i };
	}

	Vector2i operator*(int i, Vector2i v)
	{
		return v * i;
	}

	Vector2f Vector2f::operator+(Vector2f v) const
	{
		return Vector2f{ x + v.x, y + v.y };
	}

	Vector2f Vector2f::operator-(Vector2f v) const
	{
		return Vector2f{ x - v.x, y - v.y };
	}

	Vector2f Vector2f::operator*(float f) const
	{
		return Vector2f{ x * f, y * f };
	}

	Vector2f Vector2f::operator/(float f) const
	{
		return Vector2f{ x / f, y / f };
	}

	float CalculateDistance(Vector2f a, Vector2f b)
	{
		const float dx = b.x - a.x;
		const float dy = b.y - a.y;
		return std::sqrt(dx * dx + dy * dy);
	}

	bool Vector2f::operator==(Vector2f v) const
	{
		return bool{ v.x == x && v.y == y };
	}

	float Vector2f::Length() const
	{
		return std::sqrt((x * x) + (y * y));
	}

	Vector2f Vector2f::Normalize() const
	{
		return (*this / Length());
	}

	Vector2f inv(const Vector2f& v1, const Vector2f& v2)
	{
		return Vector2f{ -v2.y + v1.y, -v2.x + v1.x };
	}

	float DotProduct(Vector2f left, Vector2f right)
	{
		return left.x * right.x + left.y * right.y;
	}

	Vector2f operator*(float f, Vector2f v)
	{
		return v * f;
	}

}