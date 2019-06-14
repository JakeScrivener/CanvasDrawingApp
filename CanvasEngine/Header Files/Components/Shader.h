#pragma once
#include "BlendState.h"
#include "CullState.h"
#include "DepthState.h"

struct Shader
{
	std::wstring mFilename;
	BlendState mBlendState;
	CullState mCullState;
	DepthState  mDepthState;
};
