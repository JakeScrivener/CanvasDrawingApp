#pragma once
#include <memory>
#include <chrono>
#include "Scene.h"
#include <array>
#include "ECSManager.h"
#include "InputManager_DX.h"
#include "ThreadManager.h"

class SceneManager
{
private:
	std::chrono::nanoseconds mDeltaTime;
	std::chrono::high_resolution_clock::time_point mStartTime;
	std::chrono::high_resolution_clock::time_point mCurrentTime;
	std::chrono::high_resolution_clock::time_point mPreviousTime;

	float mWidth;
	float mHeight;

	std::shared_ptr<Scene> mScene;
	int mFps = 0;
	double mAverageDeltaTime = 0;
	std::array<double, 50> mLast50Frames;

	std::shared_ptr<ECSManager> mEcsManager = ECSManager::Instance();
	std::shared_ptr<ThreadManager> mThreadManager = ThreadManager::Instance();

#ifdef DIRECTX
	std::shared_ptr<InputManager_DX> mInputManager = InputManager_DX::Instance();
#elif OPENGL
	std::shared_ptr<InputManager_GL> mInputManager = InputManager_GL::Instance();
#endif

	SceneManager();

public:
	~SceneManager();

	void Render() const;
	void Update();
	double DeltaTime() const;
	double Time() const;
	int Fps() const;
	void SetWindowSize(const float pWidth, const float pHeight);

	inline float Width() const { return mWidth; }
	inline float Height() const { return mHeight; }

	template <class T>
	const void LoadScene()
	{
		//Create new scene of type T
		mScene = std::make_shared<T>();

		//Set start time of scene
		mStartTime = std::chrono::high_resolution_clock::now();
	};

	//Singleton pattern
	//Deleted copy constructor and assignment operator so no copies of the singleton instance can be made
	SceneManager(SceneManager const&) = delete;
	SceneManager& operator=(SceneManager const&) = delete;
	static std::shared_ptr<SceneManager> Instance();
};
