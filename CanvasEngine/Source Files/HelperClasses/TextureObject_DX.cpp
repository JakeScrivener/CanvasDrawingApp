#pragma once
#include "TextureObject_DX.h"
#include "RenderSystem_DX.h"

/// <summary>
/// 
/// </summary>
TextureObject_DX::TextureObject_DX()
{
}

/// <summary>
/// 
/// </summary>
TextureObject_DX::~TextureObject_DX()
{
}

/// <summary>
/// 
/// </summary>
/// <param name="pRenderer"></param>
/// <param name="pFilename"></param>
/// <returns></returns>
HRESULT TextureObject_DX::Create(const RenderSystem* pRenderer, const std::wstring& pFilename)
{
	HRESULT hr = S_OK;

	if (!pFilename.empty())
	{
		//Create shader resource for diffuse texture from file and store pointer to it
		hr = DirectX::CreateDDSTextureFromFile(reinterpret_cast<const RenderSystem_DX*>(pRenderer)->Device().Get(), pFilename.c_str(), nullptr, mTexture.GetAddressOf());
		if (FAILED(hr))
		{
			return hr;
		}
	}

	return hr;
}

/// <summary>
/// 
/// </summary>
/// <param name="pRenderer"></param>
void TextureObject_DX::Load(const RenderSystem * pRenderer, const int& pSlot) const
{
	reinterpret_cast<const RenderSystem_DX*>(pRenderer)->Context()->PSSetShaderResources(pSlot, 1, mTexture.GetAddressOf());
}
