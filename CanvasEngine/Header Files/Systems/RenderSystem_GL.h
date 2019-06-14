#pragma once
#include <windows.h>
#include "ECSManager.h"
#include "Components.h"
#include "ISystem.h"
#include <wrl.h>
#include "ResourceManager.h"
#include "RenderSystem.h"

struct ConstantBuffer_GL
{

};

class RenderSystem_GL : public RenderSystem
{
private:
	std::vector<Entity> mLights;
	HWND mWindow;
	UINT mWidth{};
	UINT mHeight{};
	std::shared_ptr<ECSManager> mEcsManager = ECSManager::Instance();
	std::shared_ptr<ResourceManager>  mResourceManager = ResourceManager::Instance();
	const Entity* mActiveCamera;
	ConstantBuffer_GL mCB;

	HRESULT Init() override;
	HRESULT CreateDevice() override;
	HRESULT CreateSwapChain() override;
	HRESULT CreateRenderTarget() override;
	HRESULT CreateDepth() override;
	HRESULT CreateRasterizer() override;
	HRESULT CreateBlend() override;
	HRESULT CreateSampler() override;
	void CreateViewport() const override;
	HRESULT CreateConstantBuffers();
	void Cleanup() override;

	void ClearView() const override;
	void SwapBuffers() const override;
	const VBO * const LoadGeometry(const Entity& pEntity) const override;
	void LoadShaders(const Entity& pEntity) const override;
	void LoadTexture(const Entity& pEntity) const override;

	void SetViewProj() override;
	void SetLights() override;

public:
	explicit RenderSystem_GL(const HWND& pWindow);
	virtual ~RenderSystem_GL();


	void AssignEntity(const Entity& pEntity) override;
	void ReassignEntity(const Entity& pEntity) override;
	void Process() override;
};
