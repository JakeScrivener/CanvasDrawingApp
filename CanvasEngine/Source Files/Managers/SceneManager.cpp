#include "SceneManager.h"

void SceneManager::Render() const
{
	mScene->Render();
}

void SceneManager::Update()
{
	mCurrentTime = std::chrono::high_resolution_clock::now();
	mDeltaTime = mCurrentTime - mPreviousTime;

	assert(mEcsManager->EntityCount() < 300000);
	mEcsManager->ProcessSystems();
	mScene->Update();
	mInputManager->Update();

	// Average the fps over n frames.
	mAverageDeltaTime = 0;
	for (auto i = 0; i < static_cast<int>(mLast50Frames.size() - 1); i++)
	{
		mLast50Frames[i] = mLast50Frames[i + 1];
	}
	mLast50Frames[mLast50Frames.size() - 1] = DeltaTime();

	for (auto frame : mLast50Frames)
	{
		mAverageDeltaTime += frame;
	}
	mAverageDeltaTime = mAverageDeltaTime / mLast50Frames.size();

	mFps = static_cast<int>(1 / mAverageDeltaTime);



	mPreviousTime = mCurrentTime;
}

double SceneManager::DeltaTime() const
{
	return mDeltaTime.count() / pow(10, 9); // (or 1e+9)

}

double SceneManager::Time() const
{
	auto time = mCurrentTime - mStartTime;
	return time.count() / pow(10, 9); // (or 1e+9)
}

int SceneManager::Fps() const
{
	return mFps;
}

void SceneManager::SetWindowSize(const float pWidth, const float pHeight)
{
	mWidth = pWidth;
	mHeight = pHeight;
}

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

std::shared_ptr<SceneManager> SceneManager::Instance()
{
	static std::shared_ptr<SceneManager> instance{ new SceneManager };
	return instance;
}
