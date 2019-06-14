#include "Vector3.h"

using namespace KodeBoldsMath;

/// <summary>
/// Default constructor for Vector3, initialises all values to 0
/// </summary>
Vector3::Vector3()
	:X(0), Y(0), Z(0)
{
}

/// <summary>
/// Constructor that takes 3 floats for the x, y, z and w components of the vector
/// </summary>
/// <param name="x">x component of the vector</param>
/// <param name="y">y component of the vector</param>
/// <param name="z">z component of the vector</param>
Vector3::Vector3(const float x, const float y, const float z)
	:X(x), Y(y), Z(z)
{
}

/// <summary>
/// Default destructor for Vector3
/// </summary>
Vector3::~Vector3()
{
}

/// <summary>
/// Calculates and returns the magnitude of the vector
/// </summary>
/// <returns>Magnitude of the vector</returns>
float Vector3::Magnitude() const
{
	return sqrt((X * X) + (Y * Y) + (Z * Z));
}

/// <summary>
/// Calculates and returns the dot product between this vector and a given vector
/// </summary>
/// <param name="b">Given vector to do this vector with</param>
/// <returns>Dot product of the two vectors</returns>
float Vector3::Dot(const Vector3 & b) const
{
	return (X * b.X) + (Y * b.Y) + (Z * b.Z);
}

Vector3 KodeBoldsMath::Vector3::Cross(const Vector3 & b) const
{
	return Vector3((Y * b.Z) - (Z * b.Y),
					(Z * b.X) - (X * b.Z),
					(X * b.Y) - (Y * b.X));
}

/// <summary>
/// Clamps this vector magnitude to a given value
/// </summary>
/// <param name="pMagnitude">Given magnitude to clamp to</param>
/// <returns>Clamped vector</returns>
Vector3 & Vector3::Clamp(float pMagnitude)
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
Vector3 & Vector3::Normalise()
{
	return this->Clamp(1);
}

/// <summary>
/// += operator for addition of two vector3s
/// </summary>
/// <param name="rhs">Vector to add to this vector</param>
/// <returns>Sum of the two vectors</returns>
Vector3 & Vector3::operator+=(const Vector3 & rhs)
{
	X += rhs.X;
	Y += rhs.Y;
	Z += rhs.Z;
	return *this;
}

/// <summary>
/// -= operator for the subtraction of two vector3s
/// </summary>
/// <param name="rhs">Vector to subtract from this vector</param>
/// <returns>Difference between the vectors</returns>
Vector3 & Vector3::operator-=(const Vector3 & rhs)
{
	X -= rhs.X;
	Y -= rhs.Y;
	Z -= rhs.Z;
	return *this;
}

/// <summary>
/// *= operator for the multiplication of two vector3s
/// </summary>
/// <param name="rhs">Vector to multiply this vector by</param>
/// <returns>Result of the multiplication</returns>
Vector3 & Vector3::operator*=(const float& rhs)
{
	X *= rhs;
	Y *= rhs;
	Z *= rhs;
	return *this;
}
