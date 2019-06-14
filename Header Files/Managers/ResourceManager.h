#pragma once
#include <memory>
#include <vector>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include "DDSTextureLoader.h"
#include <string>
#include "ObjLoader.h"
#include <wrl.h>
#include "VBO_DX.h"
#include "VBO_GL.h"
#include "ShaderObject_DX.h"
#include "TextureObject_DX.h"
#include "ShaderObject_GL.h"
#include "TextureObject_GL.h"


class RenderSystem;

class ResourceManager
{
	std::vector< std::pair< std::wstring, TextureObject*>> mTextures{};
	std::vector< std::pair< std::wstring, VBO*>> mGeometries{};
	std::vector< std::pair< std::wstring, ShaderObject*>> mShaders{};
	//std::vector< std::pair< string, AUDIOBUFFER>> mSounds;
	ResourceManager();

public:
	~ResourceManager();

	ResourceManager(const ResourceManager& pResourceManager) = delete;
	ResourceManager& operator=(ResourceManager const&) = delete;

	const TextureObject * const LoadTexture(const RenderSystem * const pRenderer, const std::wstring& pFilename);
	const VBO * const LoadGeometry(const RenderSystem * const pRenderer, const std::wstring& pFilename);
	//AUDIOBUFFER LoadAudio(string filename);
	const ShaderObject * const LoadShader(const RenderSystem * const pRenderer, const std::wstring& pFilename);

	static std::shared_ptr< ResourceManager > Instance();
};

