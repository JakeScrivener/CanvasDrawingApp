#pragma once
#include "ShaderObject.h"
#include <wrl.h>

class RenderSystem;

class ShaderObject_GL :
	public ShaderObject
{
private:
	//Microsoft::WRL::ComPtr<ID3D11VertexShader> mVertex;
	//Microsoft::WRL::ComPtr<ID3D11PixelShader> mPixel;
	//Microsoft::WRL::ComPtr<ID3D11InputLayout> mLayout;

	HRESULT CompileShader(const std::wstring & pFilename, const std::string& pEntryPoint, const std::string& pShaderModel, ID3DBlob** const ppBlobOut) const;

public:
	ShaderObject_GL();
	virtual ~ShaderObject_GL();

	HRESULT CreateVertex(const RenderSystem* pRenderer, const std::wstring& pFilename, const std::string& pEntryPoint, const std::string& pShaderModel) override;
	HRESULT CreatePixel(const RenderSystem* pRenderer, const std::wstring& pFilename, const std::string& pEntryPoint, const std::string& pShaderModel) override;
	void Load(const RenderSystem* pRenderer) const override;
};