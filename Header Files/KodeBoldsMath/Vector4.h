#pragma once
#include <cmath>

namespace KodeBoldsMath
{
	struct Matrix4;

	struct Vector4
	{
		float X;
		float Y;
		float Z;
		float W;

		//Structors
		Vector4();
		Vector4(const float x, const float y, const float z, const float w);
		~Vector4();

		//Maths methods
		float Magnitude() const;
		float Dot(const Vector4& b) const;
		Vector4 Cross(const Vector4& b) const;
		Vector4& Clamp(float pMagnitude);
		Vector4& Normalise();

		//Operator overloads
		Vector4& operator+=(const Vector4& rhs);
		Vector4& operator-=(const Vector4& rhs);
		Vector4& operator*=(const float& rhs);
		Vector4& operator*=(const Matrix4& rhs);
		Vector4& operator/=(const float& rhs);
	};

	//Operator overloads
	inline Vector4 operator+(Vector4 lhs, const Vector4& rhs) { lhs += rhs; return lhs; }
	inline Vector4 operator-(Vector4 lhs, const Vector4& rhs) { lhs -= rhs;	return lhs; }
	inline Vector4 operator*(Vector4 lhs, const float& rhs) { lhs *= rhs;	return lhs; }
	inline Vector4 operator*(Vector4 lhs, const Matrix4& rhs) { lhs *= rhs;	return lhs; }
	inline Vector4 operator/ (Vector4 lhs, const float& rhs) { lhs /= rhs; return lhs; }
}