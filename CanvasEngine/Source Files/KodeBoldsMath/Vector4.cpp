#include "Vector4.h"
#include "Matrix4.h"

using namespace KodeBoldsMath;

/// <summary>
/// Default constructor for Vector4, initialises all values to 0
/// </summary>
Vector4::Vector4()
	:X(0), Y(0), Z(0), W(0)
{
}

/// <summary>
/// Constructor that takes 4 floats for the x, y, z and w components of the vector
/// </summary>
/// <param name="x">x component of the vector</param>
/// <param name="y">y component of the vector</param>
/// <param name="z">z component of the vector</param>
/// <param name="w">w component of the vector</param>
Vector4::Vector4(const float x, const float y, const float z, const float w)
	:X(x), Y(y), Z(z), W(w)
{
}

/// <summary>
/// Default destructor for Vector4
/// </summary>
Vector4::~Vector4()
{
}

/// <summary>
/// Calculates and returns the magnitude of the vector
/// </summary>
/// <returns>Magnitude of the vector</returns>
float Vector4::Magnitude() const
{
	return sqrt((X * X) + (Y * Y) + (Z * Z));
}

/// <summary>
/// Calculates and returns the dot product between this vector and a given vector
/// </summary>
/// <param name="b">Given vector to do this vector with</param>
/// <returns>Dot product of the two vectors</returns>
float Vector4::Dot(const Vector4 & b) const
{
	return (X * b.X) + (Y * b.Y) + (Z * b.Z) + (W * b.W);
}

Vector4 Vector4::Cross(const Vector4 & b) const
{
	return Vector4((Y * b.Z) - (Z * b.Y),
					(Z * b.X) - (X * b.Z),
					(X * b.Y) - (Y * b.X),
					1);
}

/// <summary>
/// Clamps this vector magnitude to a given value
/// </summary>
/// <param name="pMagnitude">Given magnitude to clamp to</param>
/// <returns>Clamped vector</returns>
Vector4 & Vector4::Clamp(float pMagnitude)
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
Vector4 & Vector4::Normalise()
{
	return this->Clamp(1);
}

/// <summary>
/// += operator for addition of two vector4s
/// </summary>
/// <param name="rhs">Vector to add to this vector</param>
/// <returns>Sum of the two vectors</returns>
Vector4 & Vector4::operator+=(const Vector4 & rhs)
{
	X += rhs.X;
	Y += rhs.Y;
	Z += rhs.Z;
	W += rhs.W;
	return *this;
}

/// <summary>
/// -= operator for the subtraction of two vector4s
/// </summary>
/// <param name="rhs">Vector to subtract from this vector</param>
/// <returns>Difference between the vectors</returns>
Vector4 & Vector4::operator-=(const Vector4 & rhs)
{
	X -= rhs.X;
	Y -= rhs.Y;
	Z -= rhs.Z;
	W -= rhs.W;
	return *this;
}

/// <summary>
/// *= operator for the multiplication of two vector4s
/// </summary>
/// <param name="rhs">Vector to multiply this vector by</param>
/// <returns>Result of the multiplication</returns>
Vector4 & Vector4::operator*=(const float& rhs)
{
	X *= rhs;
	Y *= rhs;
	Z *= rhs;
	W *= rhs;
	return *this;
}

/// <summary>
/// Vector - Matrix multiplication
/// </summary>
/// <param name="rhs"> the matrix to multiply the vector by</param>
/// <returns> the vector after multiplication </returns>
Vector4 & Vector4::operator*=(const Matrix4 & rhs)
{
	X = (rhs._11 * X) + (rhs._12 * Y) + (rhs._13 * Z) + (rhs._14 * W);
	Y = (rhs._21 * X) + (rhs._22 * Y) + (rhs._23 * Z) + (rhs._24 * W);
	Z = (rhs._31 * X) + (rhs._32 * Y) + (rhs._33 * Z) + (rhs._34 * W);
	W = (rhs._41 * X) + (rhs._42 * Y) + (rhs._43 * Z) + (rhs._44 * W);
	return *this;
}

/// <summary>
/// Divide the vector by a single float
/// </summary>
/// <param name="rhs"> the float to divide by </param>
/// <returns> the vector after the division is applied </returns>
Vector4 & Vector4::operator/=(const float & rhs)
{
	X /= rhs;
	Y /= rhs;
	Z /= rhs;

	return *this;
}
