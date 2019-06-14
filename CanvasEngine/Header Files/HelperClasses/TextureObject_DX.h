#pragma once
#include "TextureObject.h"
#include "DDSTextureLoader.h"
#include <wrl.h>
#include <d3d11.h>

class RenderSystem;

class TextureObject_DX :
	public TextureObject
{
private:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mTexture;

public:
	TextureObject_DX();
	virtual ~TextureObject_DX();

	HRESULT Create(const RenderSystem* pRenderer, const std::wstring& pFilename) override;
	void Load(const RenderSystem* pRenderer, const int& pSlot) const override;
};