#pragma once
#include "TextureObject.h"
#include <wrl.h>

class RenderSystem;

class TextureObject_GL :
	public TextureObject
{
private:
	//Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mTexture;

public:
	TextureObject_GL();
	virtual ~TextureObject_GL();

	HRESULT Create(const RenderSystem* pRenderer, const std::wstring& pFilename) override;
	void Load(const RenderSystem* pRenderer, const int& pSlot) const override;
};