#include "Matrix4.h"

using namespace KodeBoldsMath;

/// <summary>
/// Default constructor that initialises the matrix to an identity matrix
/// </summary>
Matrix4::Matrix4()
	:mRows{Vector4(1, 0, 0, 0), Vector4(0, 1, 0, 0), Vector4(0, 0, 1, 0), Vector4(0, 0, 0, 1)}
{
}

/// <summary>
/// Constructor that takes 4 vectors as the 1st, 2nd, 3rd and 4th rows of the matrix
/// </summary>
/// <param name="pRow1">Row 1 of the matrix</param>
/// <param name="pRow2">Row 2 of the matrix</param>
/// <param name="pRow3">Row 3 of the matrix</param>
/// <param name="pRow4">Row 4 of the matrix</param>
Matrix4::Matrix4(const Vector4 & pRow1, const Vector4 & pRow2, const Vector4 & pRow3, const Vector4 & pRow4)
	:mRows{ pRow1, pRow2, pRow3, pRow4 }
{
}

/// <summary>
/// Constructor that takes 16 floats as the x, y, z and w components of each row of the matrix
/// </summary>
/// <param name="p11">X component of the first row of the matrix</param>
/// <param name="p12">Y component of the first row of the matrix</param>
/// <param name="p13">Z component of the first row of the matrix</param>
/// <param name="p14">W component of the first row of the matrix</param>
/// <param name="p21">X component of the second row of the matrix</param>
/// <param name="p22">Y component of the second row of the matrix</param>
/// <param name="p23">Z component of the second row of the matrix</param>
/// <param name="p24">W component of the second row of the matrix</param>
/// <param name="p31">X component of the third row of the matrix</param>
/// <param name="p32">Y component of the third row of the matrix</param>
/// <param name="p33">Z component of the third row of the matrix</param>
/// <param name="p34">W component of the third row of the matrix</param>
/// <param name="p41">X component of the fourth row of the matrix</param>
/// <param name="p42">Y component of the fourth row of the matrix</param>
/// <param name="p43">Z component of the fourth row of the matrix</param>
/// <param name="p44">W component of the fourth row of the matrix</param>
Matrix4::Matrix4(
	const float& p11, const float& p12, const float& p13, const float& p14,
	const float& p21, const float& p22, const float& p23, const float& p24,
	const float& p31, const float& p32, const float& p33, const float& p34,
	const float& p41, const float& p42, const float& p43, const float& p44)
	:mRows{ Vector4(p11, p12, p13, p14), Vector4(p21, p22, p23, p24), Vector4(p31, p32, p33, p34), Vector4(p41, p42, p43, p44) }
{
}

/// <summary>
/// Default destructor for Matrix4
/// </summary>
Matrix4::~Matrix4()
{
}


/// <summary>
/// Multiplies this matrix with a given matrix
/// </summary>
/// <param name="rhs">Given matrix to multiply by</param>
/// <returns>Result of the multiplication</returns>
Matrix4 & Matrix4::operator*=(const Matrix4 & rhs)
{
	//Calculates dot product of the 1st row with each column of the given matrix to get the new values for the 1st row of the matrix
	mRows[0] = Vector4(
		mRows[0].Dot(Vector4(rhs._11, rhs._21, rhs._31, rhs._41)),
		mRows[0].Dot(Vector4(rhs._12, rhs._22, rhs._32, rhs._42)),
		mRows[0].Dot(Vector4(rhs._13, rhs._23, rhs._33, rhs._43)),
		mRows[0].Dot(Vector4(rhs._14, rhs._24, rhs._34, rhs._44)));

	//Calculates dot product of the 2nd row with each column of the given matrix to get the new values for the 2nd row of the matrix
	mRows[1] = Vector4(
		mRows[1].Dot(Vector4(rhs._11, rhs._21, rhs._31, rhs._41)),
		mRows[1].Dot(Vector4(rhs._12, rhs._22, rhs._32, rhs._42)),
		mRows[1].Dot(Vector4(rhs._13, rhs._23, rhs._33, rhs._43)),
		mRows[1].Dot(Vector4(rhs._14, rhs._24, rhs._34, rhs._44)));

	//Calculates dot product of the 3rd row with each column of the given matrix to get the new values for the 3rd row of the matrix
	mRows[2] = Vector4(
		mRows[2].Dot(Vector4(rhs._11, rhs._21, rhs._31, rhs._41)),
		mRows[2].Dot(Vector4(rhs._12, rhs._22, rhs._32, rhs._42)),
		mRows[2].Dot(Vector4(rhs._13, rhs._23, rhs._33, rhs._43)),
		mRows[2].Dot(Vector4(rhs._14, rhs._24, rhs._34, rhs._44)));

	//Calculates dot product of the 4th row with each column of the given matrix to get the new values for the 4th row of the matrix
	mRows[3] = Vector4(
		mRows[3].Dot(Vector4(rhs._11, rhs._21, rhs._31, rhs._41)),
		mRows[3].Dot(Vector4(rhs._12, rhs._22, rhs._32, rhs._42)),
		mRows[3].Dot(Vector4(rhs._13, rhs._23, rhs._33, rhs._43)),
		mRows[3].Dot(Vector4(rhs._14, rhs._24, rhs._34, rhs._44)));

	return *this;
}

