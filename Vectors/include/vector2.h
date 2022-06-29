#pragma once

namespace gpr4400
{

	struct Vector2i
	{
		int x, y;
		Vector2i operator+(Vector2i v) const;
		Vector2i operator-(Vector2i v) const;
		Vector2i operator*(int i) const;
		Vector2i operator/(int i) const;
		bool operator==(const Vector2i&) const = default;
	};

	Vector2i operator*(int i, Vector2i v);

	struct Vector2f
	{
		float x, y;
		Vector2f operator+(Vector2f v) const;
		Vector2f operator-(Vector2f v) const;
		Vector2f operator*(float f) const;
		Vector2f operator/(float f) const;
		bool operator == (Vector2f v) const;
		float Length() const;
		Vector2f Normalize() const;
	};

	Vector2f inv(const Vector2f& v1, const Vector2f& v2);
	float DotProduct(Vector2f left, Vector2f right);
	float CalculateDistance(Vector2f a, Vector2f b);
	Vector2f operator*(float f, Vector2f v);

}