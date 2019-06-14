#pragma once
#include "Scene.h"
#include "KodeBoldsMath.h"
#include "Managers.h"
#include "GameValues.h"
#include "FrequencyValues.h"

class GameScene : public Scene
{
	std::shared_ptr<ECSManager> mEcsManager = ECSManager::Instance();

#ifdef DIRECTX
	std::shared_ptr<InputManager_DX> mInputManager = InputManager_DX::Instance();
#elif OPENGL
	std::shared_ptr<InputManager_GL> mInputManager = InputManager_GL::Instance();
#endif

	std::shared_ptr<SceneManager> mSceneManager = SceneManager::Instance();
	std::shared_ptr<AntTweakManager> mAntTweakManager = AntTweakManager::Instance();
	std::shared_ptr<NetworkManager> mNetworkManager = NetworkManager::Instance();

	KodeBoldsMath::Matrix4 mView;
	KodeBoldsMath::Matrix4 mProj;
	KodeBoldsMath::Vector4 mEye;
	KodeBoldsMath::Vector4 mLookAt;
	KodeBoldsMath::Vector4 mUp;

	float mWidth;
	float mHeight;

	int mRayID;
	int mCameraID;

	int mCubeCount;
	int mLastCollided;

	bool mIntegrityMode = false;
	
	void CameraControls(const float& pDt);
	void Reset();

public:
	GameScene();
	~GameScene();

	void Render() override;
	void Update() override;
	void OnLoad() override;
};
