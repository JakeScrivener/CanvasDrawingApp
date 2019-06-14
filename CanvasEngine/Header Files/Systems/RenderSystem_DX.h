#pragma once
#include <windows.h>
#include "ECSManager.h"
#include "Components.h"
#include "ISystem.h"
#include "Vector4.h"
#include <d3d11shader.h>
#include <d3d11.h>
#include <d3d11_1.h>
#include <wrl.h>
#include <directxcolors.h>
#include "ResourceManager.h"
#include "RenderSystem.h"
#include "AntTweakManager.h"
#include "ThreadManager.h"
#include <array>
#include "FrequencyValues.h"

struct ConstantBuffer
{
	DirectX::XMFLOAT4X4 mWorld;
	DirectX::XMFLOAT4X4 mView;
	DirectX::XMFLOAT4X4 mProj;
	DirectX::XMFLOAT4 mLightColour;
	DirectX::XMFLOAT4 mLightPosition;
	DirectX::XMFLOAT4 mCameraPosition;
	DirectX::XMFLOAT4 mColour;
};

class RenderSystem_DX : public RenderSystem
{
private:
	std::vector<Entity> mLights;
	HWND mWindow;
	UINT mWidth{};
	UINT mHeight{};
	std::shared_ptr<ECSManager> mEcsManager = ECSManager::Instance();
	std::shared_ptr<ResourceManager>  mResourceManager = ResourceManager::Instance();
	std::shared_ptr<AntTweakManager> mAntTweakManager = AntTweakManager::Instance();
	std::shared_ptr<ThreadManager> mThreadManager = ThreadManager::Instance();
	const Entity* mActiveCamera;
	ConstantBuffer mCB{};

	/// <summary>
	/// DirectX pointers
	/// </summary>
	D3D_FEATURE_LEVEL mFeatureLevel = D3D_FEATURE_LEVEL_11_0;
	Microsoft::WRL::ComPtr<ID3D11Device> mDevice = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Device1> mDevice1 = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> mContext = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext1> mContext1 = nullptr;
	Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain = nullptr;
	Microsoft::WRL::ComPtr<IDXGISwapChain1> mSwapChain1 = nullptr;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRenderTargetView = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> mDepthStencil = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mDepthStencilView = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> mDepthStencilState = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer> mConstantBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer> mConstantBufferUniform = nullptr;
	Microsoft::WRL::ComPtr<ID3D11SamplerState> mTexSampler = nullptr;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> mDefaultRasterizerState = nullptr;

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

	std::wstring mActiveShader;
	std::wstring mActiveGeometryName;

	const VBO* mActiveGeometry{};

	void CalculateFreq();
	std::chrono::nanoseconds mDeltaTime{};
	std::chrono::high_resolution_clock::time_point mStartTime;
	std::chrono::high_resolution_clock::time_point mCurrentTime;
	std::chrono::high_resolution_clock::time_point mPreviousTime;

	int mActualFrequency{};
	double mAverageDeltaTime = 0;
	double mTargetDeltaTime = 0;
	std::array<double, 50> mLast50Frames{};
	double mSleepTime{};

	std::mutex mx;

public:
	explicit RenderSystem_DX(const HWND& pWindow);
	virtual ~RenderSystem_DX();

	void AssignEntity(const Entity& pEntity) override;
	void ReassignEntity(const Entity& pEntity) override;
	void Process() override;
	Microsoft::WRL::ComPtr<ID3D11Device> Device() const { return mDevice; }
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> Context() const { return mContext; }

};
