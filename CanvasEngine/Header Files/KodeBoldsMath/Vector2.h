#pragma once
#include <cmath>

namespace KodeBoldsMath
{
	struct Vector2
	{
		float X;
		float Y;

		//Structors
		Vector2();
		Vector2(const float x, const float y);
		~Vector2();

		//Maths methods
		float Magnitude() const;
		float Dot(const Vector2& b) const;
		Vector2& Clamp(float pMagnitude);
		Vector2& Normalise();
		
		//Operator overloads
		Vector2& operator+=(const Vector2& rhs);
		Vector2& operator-=(const Vector2& rhs);
		Vector2& operator*=(const float& rhs);
	};

	//Operator overloads
	inline Vector2 operator+(Vector2 lhs, const Vector2& rhs) { lhs += rhs; return lhs; }
	inline Vector2 operator-(Vector2 lhs, const Vector2& rhs) { lhs -= rhs;	return lhs; }
	inline Vector2 operator*(Vector2 lhs, const float& rhs) { lhs *= rhs;	return lhs; }
}