#pragma once
#include <windows.h>
#include <iostream>
#include <thread>
#include "ThreadManager.h"

class Thread
{
private:
	int mId;
	std::thread mThread;

	std::shared_ptr<ThreadManager> mThreadManager = ThreadManager::Instance();

	bool mIsRunning = false;
	std::function<void(void*, void*)> mFunction = nullptr;

public:
	Thread(int pId);
	~Thread();

	void Run();
	void Start();
	void Finish();
	bool IsRunning() const;
	void SetAffinity(const std::vector<int>& pCore);
};
