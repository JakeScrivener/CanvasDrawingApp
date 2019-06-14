#pragma once
#include <cmath>

namespace KodeBoldsMath
{
	struct Vector3
	{
		float X;
		float Y;
		float Z;

		//Structors
		Vector3();
		Vector3(const float x, const float y, const float z);
		~Vector3();

		//Maths methods
		float Magnitude() const;
		float Dot(const Vector3& b) const;
		Vector3 Cross(const Vector3& b) const;
		Vector3& Clamp(float pMagnitude);
		Vector3& Normalise();

		//Operator overloads
		Vector3& operator+=(const Vector3& rhs);
		Vector3& operator-=(const Vector3& rhs);
		Vector3& operator*=(const float& rhs);
	};

	//Operator overloads
	inline Vector3 operator+(Vector3 lhs, const Vector3& rhs) { lhs += rhs; return lhs; }
	inline Vector3 operator-(Vector3 lhs, const Vector3& rhs) { lhs -= rhs;	return lhs; }
	inline Vector3 operator*(Vector3 lhs, const float& rhs) { lhs *= rhs;	return lhs; }
}