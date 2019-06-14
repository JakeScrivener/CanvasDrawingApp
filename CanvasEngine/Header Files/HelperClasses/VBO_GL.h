#pragma once
#include "VBO.h"
#include "ObjLoader.h"

class RenderSystem;

class VBO_GL :
	public VBO
{
private:
	//Microsoft::WRL::ComPtr<ID3D11Buffer> mVertices{};
	//Microsoft::WRL::ComPtr<ID3D11Buffer> mIndices{};

public:
	VBO_GL();
	~VBO_GL();

	HRESULT Create(const RenderSystem* pRenderer, const std::wstring& pFilename) override;
	void Load(const RenderSystem* pRenderer) const override;
	void Draw(const RenderSystem* pRenderer) const override;

	//Microsoft::WRL::ComPtr<ID3D11Buffer> Vertices() const { return mVertices; }
	//Microsoft::WRL::ComPtr<ID3D11Buffer> Indices() const { return mIndices; }
};

