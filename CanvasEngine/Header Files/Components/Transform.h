#pragma once
#include "Vector4.h"
#include "Matrix4.h"

struct Transform
{
	KodeBoldsMath::Matrix4 mTransform;
	KodeBoldsMath::Vector4 mTranslation;
	KodeBoldsMath::Vector4 mRotation;
	KodeBoldsMath::Vector4 mScale;
	KodeBoldsMath::Vector4 mForward;
	KodeBoldsMath::Vector4 mRight;
	KodeBoldsMath::Vector4 mUp;
};