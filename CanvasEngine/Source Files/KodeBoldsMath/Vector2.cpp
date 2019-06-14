#include "Vector2.h"

using namespace KodeBoldsMath;

/// <summary>
/// Default constructor for Vector4, initialises all values to 0
/// </summary>
Vector2::Vector2()
	:X(0), Y(0)
{
}

/// <summary>
/// Constructor that takes 4 floats for the x, y, z and w components of the vector
/// </summary>
/// <param name="x">x component of the vector</param>
/// <param name="y">y component of the vector</param>
/// <param name="z">z component of the vector</param>
/// <param name="w">w component of the vector</param>
Vector2::Vector2(const float x, const float y)
	:X(x), Y(y)
{
}

/// <summary>
/// Default destructor for Vector4
/// </summary>
Vector2::~Vector2()
{
}

/// <summary>
/// Calculates and returns the magnitude of the vector
/// </summary>
/// <returns>Magnitude of the vector</returns>
float Vector2::Magnitude() const
{
	return sqrt((X * X) + (Y * Y));
}

/// <summary>
/// Calculates and returns the dot product between this vector and a given vector
/// </summary>
/// <param name="b">Given vector to do this vector with</param>
/// <returns>Dot product of the two vectors</returns>
float Vector2::Dot(const Vector2 & b) const
{
	return (X * b.X) + (Y * b.Y);
}

/// <summary>
/// Clamps this vector magnitude to a given value
/// </summary>
/// <param name="pMagnitude">Given magnitude to clamp to</param>
/// <returns>Clamped vector</returns>
Vector2 & Vector2::Clamp(float pMagnitude)
{
	float magnitude = this->Magnitude();
	if (magnitude > pMagnitude)
	{
		float scale = pMagnitude / magnitude;
		return *this *= scale;
	}
	return *this;
}

/// <summary>
/// Normalises this vector
/// </summary>
/// <returns>Normalised vector</returns>
Vector2 & Vector2::Normalise()
{
	return this->Clamp(1);
}

/// <summary>
/// += operator for addition of two vector4s
/// </summary>
/// <param name="rhs">Vector to add to this vector</param>
/// <returns>Sum of the two vectors</returns>
Vector2& Vector2::operator+=(const Vector2 & rhs)
{
	X += rhs.X;
	Y += rhs.Y;
	return *this;
}

/// <summary>
/// -= operator for the subtraction of two vector4s
/// </summary>
/// <param name="rhs">Vector to subtract from this vector</param>
/// <returns>Difference between the vectors</returns>
Vector2& Vector2::operator-=(const Vector2 & rhs)
{
	X -= rhs.X;
	Y -= rhs.Y;
	return *this;
}

/// <summary>
/// *= operator for the multiplication of two vector4s
/// </summary>
/// <param name="rhs">Vector to multiply this vector by</param>
/// <returns>Result of the multiplication</returns>
Vector2& Vector2::operator*=(const float& rhs)
{
	X *= rhs;
	Y *= rhs;
	return *this;
}
