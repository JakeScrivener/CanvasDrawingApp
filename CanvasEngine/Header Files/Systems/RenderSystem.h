#pragma once
#include "ISystem.h"
#include "wrl.h"
#include "VBO.h"


class RenderSystem : public ISystem
{
protected:
	RenderSystem(const ComponentType& pMask);

public:
	virtual ~RenderSystem() {};

	virtual HRESULT Init() = 0;
	virtual HRESULT CreateDevice() = 0;
	virtual HRESULT CreateSwapChain() = 0;
	virtual HRESULT CreateRenderTarget() = 0;
	virtual HRESULT CreateDepth() = 0;
	virtual HRESULT CreateRasterizer() = 0;
	virtual HRESULT CreateBlend() = 0;
	virtual HRESULT CreateSampler() = 0;
	virtual void CreateViewport() const = 0;
	virtual void Cleanup() = 0;

	virtual void ClearView() const = 0;
	virtual void SwapBuffers() const = 0;
	virtual const VBO * const LoadGeometry(const Entity& pEntity) const = 0;
	virtual void LoadShaders(const Entity& pEntity) const = 0;
	virtual void LoadTexture(const Entity& pEntity) const = 0;
	virtual void SetViewProj() = 0;
	virtual void SetLights() = 0;
};
