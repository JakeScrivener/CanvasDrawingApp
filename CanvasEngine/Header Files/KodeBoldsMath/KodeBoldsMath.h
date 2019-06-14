#pragma once
#include "Matrix4.h"
#include <cmath>
#include <assert.h>
#include "Vector2.h"
#include "Vector3.h"

namespace KodeBoldsMath
{
	const double PI = 3.141592653589793238463;

	/// <summary>
	/// Creates an identity matrix
	/// </summary>
	/// <returns>Returns an identity matrix</returns>
	static Matrix4 Identity()
	{
		return Matrix4(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);
	}

	/// <summary>
	/// Creates a 
	/// </summary>
	/// <param name="pFov"></param>
	/// <param name="pAspectRatio"></param>
	/// <param name="pNear"></param>
	/// <param name="pFar"></param>
	/// <returns></returns>
	static Matrix4 ProjectionLH(const float pFov, const float pAspectRatio, const float pNear, const float pFar)
	{
		assert(pFov > 0 && pAspectRatio != 0);

		const float frustrumDepth = pFar - pNear;
		const float inverseDepth = 1 / frustrumDepth;

		Matrix4 proj;
		proj._22 = 1 / tan(0.5f * pFov);
		proj._11 = proj._22 / pAspectRatio;
		proj._33 = pFar * inverseDepth;
		proj._43 = (-pFar * pNear) * inverseDepth;
		proj._34 = 1;
		proj._44 = 0;

		return proj;
	}


	/// <summary>
	/// Creates a view matrix based on a left handed coordinate system
	/// </summary>
	/// <param name="pEye"></param>
	/// <param name="pLook"></param>
	/// <param name="pUp"></param>
	/// <returns></returns>
	static Matrix4 LookAtLH(const Vector4& pEye, const Vector4& pLook, const Vector4& pUp)
	{
		const Vector4 zAxis = Vector4(pLook - pEye).Normalise();
		const Vector4 xAxis = pUp.Cross(zAxis).Normalise();
		const Vector4 yAxis = zAxis.Cross(xAxis);

		Matrix4 view(
			xAxis.X,			 yAxis.X,			zAxis.X,			0,
			xAxis.Y,			 yAxis.Y,			zAxis.Y,			0,
			xAxis.Z,			 yAxis.Z,			zAxis.Z,			0,
			-xAxis.Dot(pEye),	-yAxis.Dot(pEye),	-zAxis.Dot(pEye),	1);

		return view;
	}

	/// <summary>
	/// Creates a rotation matrix around the y axis with a given angle in radians
	/// </summary>
	/// <param name="pAngle">Given angle of rotation</param>
	/// <returns>Rotation matrix for a rotation around the x axis</returns>
	static Matrix4 RotationMatrixX(const float& pAngle)
	{
		//Sin and cosin of angle
		float s = sin(pAngle);
		float c = cos(pAngle);

		Matrix4 matrix(
			1, 0, 0, 0,
			0, c, s, 0,
			0, -s, c, 0,
			0, 0, 0, 1);

		return matrix;
	}

	/// <summary>
	/// Creates a rotation matrix around the y axis with a given angle in radians
	/// </summary>
	/// <param name="pAngle">Given angle of rotation</param>
	/// <returns>Rotation matrix for a rotation around the y axis</returns>
	static Matrix4 RotationMatrixY(const float& pAngle)
	{
		//Sin and cosin of angle
		float s = sin(pAngle);
		float c = cos(pAngle);

		Matrix4 matrix(
			c, 0, -s, 0,
			0, 1, 0, 0,
			s, 0, c, 0,
			0, 0, 0, 1);

		return matrix;
	}

	/// <summary>
	/// Creates a rotation matrix around the z axis with a given angle in radians
	/// </summary>
	/// <param name="pAngle">Given angle of rotation</param>
	/// <returns>Rotation matrix for a rotation around the z axis</returns>
	static Matrix4 RotationMatrixZ(const float& pAngle)
	{
		//Sin and cosin of angle
		float s = sin(pAngle);
		float c = cos(pAngle);

		Matrix4 matrix(
			c, s, 0, 0,
			-s, c, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);

		return matrix;
	}

	/// <summary>
	/// Creates a rotation matrix around a given axis with a given angle in radians
	/// </summary>
	/// <param name="pAngle">Given angle of rotation</param>
	/// <param name="pAxis">Given axis to rotation around</param>
	/// <returns>Rotation matrix for a rotation around the given axis</returns>
	static Matrix4 RotationMatrixAxis(const float& pAngle, const Vector4& pAxis)
	{
		//Sin and cosin of angle
		const float s = sin(pAngle);
		const float c = cos(pAngle);
		const float oneSubC = 1 - c;

		//Squares of x, y and z components of axis
		const float xSqrd = pAxis.X * pAxis.X;
		const float ySqrd = pAxis.Y * pAxis.Y;
		const float zSqrd = pAxis.Z * pAxis.Z;

		//X, y and z components multiplied by sin
		const float xS = pAxis.X * s;
		const float yS = pAxis.Y * s;
		const float zS = pAxis.Z * s;

		//X, y and z components multiplied by each other component
		const float xY = pAxis.X * pAxis.Y;
		const float xZ = pAxis.X * pAxis.Z;
		const float yZ = pAxis.Y * pAxis.Z;

		Matrix4 matrix(
			//Column 1             // Column 2            //Column 3             //Column 4
			(c + xSqrd) * oneSubC, (xY * oneSubC) - zS,   (xZ * oneSubC) + yS,   0,  //Row 1
			(xY * oneSubC) + zS,   (c + ySqrd) * oneSubC, (yZ * oneSubC) - xS,   0,  //Row 2
			(xZ * oneSubC) - yS,   (yZ * oneSubC) + xS,   (c + zSqrd) * oneSubC, 0,  //Row 3
			0, 0, 0, 1); //Row 4

		return matrix;
	}

	/// <summary>
	/// Creates a translation matrix from a given vector
	/// </summary>
	/// <param name="pVector">Given vector containing x, y, z components of translation</param>
	/// <returns>Translation matrix containing the given translation vector</returns>
	static Matrix4 TranslationMatrix(const Vector4& pVector)
	{
		Matrix4 matrix(
			1, 0, 0, pVector.X,
			0, 1, 0, pVector.Y,
			0, 0, 1, pVector.Z,
			0, 0, 0, 1);

		return matrix;
	}

	/// <summary>
	/// Creates a scale matrix from a given vector
	/// </summary>
	/// <param name="pVector">Given vector containing x, y, z components of scale</param>
	/// <returns>Scale matrix containing the given scale vector</returns>
	static Matrix4 ScaleMatrix(const Vector4& pVector)
	{
		Matrix4 matrix(
			pVector.X, 0, 0, 0,
			0, pVector.Y, 0, 0,
			0, 0, pVector.Z, 0,
			0, 0, 0, 1);

		return matrix;
	}

	/// <summary>
	/// Calculates the transpose of a given matrix
	/// </summary>
	/// <param name="pMatrix">Given matrix to transpose</param>
	/// <returns>Transposed matrix of the given matrix</returns>
	static Matrix4 Transpose(const Matrix4& pMatrix)
	{
		Matrix4 matrix(
			pMatrix._11, pMatrix._21, pMatrix._31, pMatrix._41,
			pMatrix._12, pMatrix._21, pMatrix._32, pMatrix._42,
			pMatrix._13, pMatrix._23, pMatrix._33, pMatrix._43,
			pMatrix._14, pMatrix._24, pMatrix._34, pMatrix._44);

		return matrix;
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="pMatrix"></param>
	/// <returns></returns>
	static Matrix4 Inverse(const Matrix4& pMatrix)
	{
		float det = 
			(pMatrix._11 * pMatrix._22 * pMatrix._33 * pMatrix._44) +
			(pMatrix._11 * pMatrix._23 * pMatrix._34 * pMatrix._42) +
			(pMatrix._11 * pMatrix._24 * pMatrix._32 * pMatrix._43) +

			(pMatrix._12 * pMatrix._21 * pMatrix._34 * pMatrix._43) +
			(pMatrix._12 * pMatrix._23 * pMatrix._31 * pMatrix._44) +
			(pMatrix._12 * pMatrix._24 * pMatrix._33 * pMatrix._41) +

			(pMatrix._13 * pMatrix._21 * pMatrix._32 * pMatrix._44) +
			(pMatrix._13 * pMatrix._22 * pMatrix._34 * pMatrix._41) +
			(pMatrix._13 * pMatrix._24 * pMatrix._31 * pMatrix._42) +

			(pMatrix._14 * pMatrix._21 * pMatrix._33 * pMatrix._42) +
			(pMatrix._14 * pMatrix._22 * pMatrix._31 * pMatrix._43) +
			(pMatrix._14 * pMatrix._23 * pMatrix._32 * pMatrix._41) -

			(pMatrix._11 * pMatrix._22 * pMatrix._34 * pMatrix._43) -
			(pMatrix._11 * pMatrix._23 * pMatrix._32 * pMatrix._44) -
			(pMatrix._11 * pMatrix._24 * pMatrix._33 * pMatrix._42) -

			(pMatrix._12 * pMatrix._21 * pMatrix._33 * pMatrix._44) -
			(pMatrix._12 * pMatrix._23 * pMatrix._34 * pMatrix._41) -
			(pMatrix._12 * pMatrix._24 * pMatrix._31 * pMatrix._43) -

			(pMatrix._13 * pMatrix._21 * pMatrix._34 * pMatrix._42) -
			(pMatrix._13 * pMatrix._22 * pMatrix._31 * pMatrix._44) -
			(pMatrix._13 * pMatrix._24 * pMatrix._32 * pMatrix._41) -

			(pMatrix._14 * pMatrix._21 * pMatrix._32 * pMatrix._43) -
			(pMatrix._14 * pMatrix._22 * pMatrix._33 * pMatrix._41) -
			(pMatrix._14 * pMatrix._23 * pMatrix._31 * pMatrix._42);

		
		assert(det != 0);

		Matrix4 inv;
		//Row 1 Column 1
		inv._11 =
			pMatrix._22 * pMatrix._33 * pMatrix._44 +
			pMatrix._23 * pMatrix._34 * pMatrix._42 +
			pMatrix._24 * pMatrix._32 * pMatrix._43 -
			pMatrix._22 * pMatrix._34 * pMatrix._43 -
			pMatrix._23 * pMatrix._32 * pMatrix._44 -
			pMatrix._24 * pMatrix._33 * pMatrix._42;

		//Row 1 Column 2
		inv._12 =
			pMatrix._12 * pMatrix._33 * pMatrix._43 +
			pMatrix._13 * pMatrix._32 * pMatrix._44 +
			pMatrix._14 * pMatrix._33 * pMatrix._42 -
			pMatrix._12 * pMatrix._33 * pMatrix._44 -
			pMatrix._13 * pMatrix._34 * pMatrix._42 -
			pMatrix._14 * pMatrix._32 * pMatrix._43;

		//Row 1 Column 3
		inv._13 =
			pMatrix._12 * pMatrix._23 * pMatrix._44 +
			pMatrix._13 * pMatrix._24 * pMatrix._42 +
			pMatrix._14 * pMatrix._22 * pMatrix._43 -
			pMatrix._12 * pMatrix._24 * pMatrix._43 -
			pMatrix._13 * pMatrix._22 * pMatrix._44 -
			pMatrix._14 * pMatrix._23 * pMatrix._42;

		//Row 1 Column 4
		inv._14 =
			pMatrix._12 * pMatrix._24 * pMatrix._33 +
			pMatrix._13 * pMatrix._22 * pMatrix._34 +
			pMatrix._14 * pMatrix._23 * pMatrix._32 -
			pMatrix._12 * pMatrix._23 * pMatrix._34 -
			pMatrix._13 * pMatrix._24 * pMatrix._32 -
			pMatrix._14 * pMatrix._22 * pMatrix._33;

		//Row 2 Column 1
		inv._21 =
			pMatrix._21 * pMatrix._34 * pMatrix._43 +
			pMatrix._23 * pMatrix._31 * pMatrix._44 +
			pMatrix._24 * pMatrix._33 * pMatrix._41 -
			pMatrix._21 * pMatrix._33 * pMatrix._44 -
			pMatrix._23 * pMatrix._34 * pMatrix._41 -
			pMatrix._24 * pMatrix._31 * pMatrix._43;

		//Row 2 Column 2
		inv._22 =
			pMatrix._11 * pMatrix._33 * pMatrix._44 +
			pMatrix._13 * pMatrix._34 * pMatrix._41 +
			pMatrix._14 * pMatrix._31 * pMatrix._43 -
			pMatrix._11 * pMatrix._34 * pMatrix._43 -
			pMatrix._13 * pMatrix._31 * pMatrix._44 -
			pMatrix._14 * pMatrix._33 * pMatrix._41;

		//Row 2 Column 3
		inv._23 =
			pMatrix._11 * pMatrix._24 * pMatrix._43 +
			pMatrix._13 * pMatrix._21 * pMatrix._44 +
			pMatrix._14 * pMatrix._23 * pMatrix._41 -
			pMatrix._11 * pMatrix._23 * pMatrix._44 -
			pMatrix._13 * pMatrix._24 * pMatrix._41 -
			pMatrix._14 * pMatrix._21 * pMatrix._43;

		//Row 2 Column 4
		inv._24 =
			pMatrix._11 * pMatrix._23 * pMatrix._34 +
			pMatrix._13 * pMatrix._24 * pMatrix._31 +
			pMatrix._14 * pMatrix._21 * pMatrix._33 -
			pMatrix._11 * pMatrix._24 * pMatrix._33 -
			pMatrix._13 * pMatrix._21 * pMatrix._34 -
			pMatrix._14 * pMatrix._23 * pMatrix._31;

		//Row 3 Column 1
		inv._31 =
			pMatrix._21 * pMatrix._32 * pMatrix._44 +
			pMatrix._22 * pMatrix._34 * pMatrix._41 +
			pMatrix._24 * pMatrix._31 * pMatrix._42 -
			pMatrix._21 * pMatrix._34 * pMatrix._42 -
			pMatrix._22 * pMatrix._31 * pMatrix._44 -
			pMatrix._24 * pMatrix._32 * pMatrix._41;

		//Row 3 Column 2
		inv._32 =
			pMatrix._11 * pMatrix._34 * pMatrix._42 +
			pMatrix._12 * pMatrix._31 * pMatrix._44 +
			pMatrix._14 * pMatrix._32 * pMatrix._41 -
			pMatrix._11 * pMatrix._32 * pMatrix._44 -
			pMatrix._12 * pMatrix._34 * pMatrix._41 -
			pMatrix._14 * pMatrix._31 * pMatrix._42;

		//Row 3 Column 3
		inv._33 =
			pMatrix._11 * pMatrix._22 * pMatrix._44 +
			pMatrix._12 * pMatrix._24 * pMatrix._41 +
			pMatrix._14 * pMatrix._21 * pMatrix._42 -
			pMatrix._11 * pMatrix._24 * pMatrix._42 -
			pMatrix._12 * pMatrix._21 * pMatrix._44 -
			pMatrix._14 * pMatrix._22 * pMatrix._41;

		//Row 3 Column 4
		inv._34 =
			pMatrix._11 * pMatrix._24 * pMatrix._32 +
			pMatrix._12 * pMatrix._21 * pMatrix._34 +
			pMatrix._14 * pMatrix._22 * pMatrix._31 -
			pMatrix._11 * pMatrix._22 * pMatrix._34 -
			pMatrix._12 * pMatrix._24 * pMatrix._31 -
			pMatrix._14 * pMatrix._21 * pMatrix._32;

		//Row 4 Column 1
		inv._41 =
			pMatrix._21 * pMatrix._33 * pMatrix._42 +
			pMatrix._22 * pMatrix._31 * pMatrix._43 +
			pMatrix._23 * pMatrix._32 * pMatrix._41 -
			pMatrix._21 * pMatrix._32 * pMatrix._43 -
			pMatrix._22 * pMatrix._33 * pMatrix._41 -
			pMatrix._23 * pMatrix._31 * pMatrix._42;

		//Row 4 Column 2
		inv._42 =
			pMatrix._11 * pMatrix._32 * pMatrix._43 +
			pMatrix._12 * pMatrix._33 * pMatrix._41 +
			pMatrix._13 * pMatrix._31 * pMatrix._42 -
			pMatrix._11 * pMatrix._33 * pMatrix._42 -
			pMatrix._12 * pMatrix._31 * pMatrix._43 -
			pMatrix._13 * pMatrix._32 * pMatrix._41;

		//Row 4 Column 3
		inv._43 =
			pMatrix._11 * pMatrix._23 * pMatrix._42 +
			pMatrix._12 * pMatrix._21 * pMatrix._43 +
			pMatrix._13 * pMatrix._22 * pMatrix._41 -
			pMatrix._11 * pMatrix._22 * pMatrix._43 -
			pMatrix._12 * pMatrix._23 * pMatrix._41 -
			pMatrix._13 * pMatrix._21 * pMatrix._42;

		//Row 4 Column 4
		inv._44 =
			pMatrix._11 * pMatrix._22 * pMatrix._33 +
			pMatrix._12 * pMatrix._23 * pMatrix._31 +
			pMatrix._13 * pMatrix._21 * pMatrix._32 -
			pMatrix._11 * pMatrix._23 * pMatrix._32 -
			pMatrix._12 * pMatrix._21 * pMatrix._33 -
			pMatrix._13 * pMatrix._22 * pMatrix._31;

		//Calculate 1/determinant and multiply each element of the matrix by it
		det = 1.0f / det;
		for (auto& element : inv.mElements)
		{
			element = element * det;
		}


		return inv;
	}

	/// <summary>
	///  Converts given angle from degrees to radians
	/// </summary>
	/// <returns>Returns given angle in radians</returns>
	static float DegreesToRadians(const float& pAngle)
	{
		return static_cast<float>((pAngle * PI) / 180);
	}

	/// <summary>
	/// Converts given angle from radians to degrees
	/// </summary>
	/// <returns>REturns given angle in degrees</returns>
	static float RadiansToDegrees(const float& pAngle)
	{
		return static_cast<float>((pAngle * 180) / PI);
	}
}