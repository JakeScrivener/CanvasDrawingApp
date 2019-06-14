#pragma once
#include <wrl.h>
#include <string>

class RenderSystem;

class VBO
{
protected:
	VBO() = default;

	int mIndexCount;
public:
	virtual ~VBO() = default;

	virtual HRESULT Create(const RenderSystem* pRenderer, const std::wstring& pFilename) = 0;
	virtual void Load(const RenderSystem* pRenderer) const = 0;
	virtual void Draw(const RenderSystem* pRenderer) const = 0;
	//virtual void* Vertices() const = 0;
	//virtual void* Indices() const = 0;
};
