#include "Thread.h"

using namespace std;

Thread::Thread(const int pId)
{
	mId = pId;
	Start();
}

Thread::~Thread()
{
}

/// <summary>
/// the static thread main
/// </summary>
auto threadMain = [](Thread* pTask)
{
	pTask->Run();
	return 0;
};

/// <summary>
/// The run function of the thread, runs the current
/// </summary>
void Thread::Run()
{
	while (true)
	{
		if (!mFunction)
		{
			auto task = mThreadManager->GetTask();
			mFunction = task.Function();
			if (mFunction)
			{
				SetAffinity(task.Cores());
				mIsRunning = true;
				const auto data = task.Data();
				mFunction(data.first, data.second);
				mIsRunning = false;
				mThreadManager->CompleteTask(mFunction);
				mFunction = nullptr;
			}
		}
		Sleep(1);
	}

}

void Thread::Start()
{
	mThread = thread(threadMain, this);
}

void Thread::Finish()
{
	mThread.join();
}

bool Thread::IsRunning() const
{
	return mIsRunning;
}

void Thread::SetAffinity(const std::vector<int>& pCore)
{
	long long mask = 0;
	for (const auto& core : pCore)
	{
		int bitShift = core - 1;
		mask += 1i64 << bitShift;
	}
	SetThreadAffinityMask(mThread.native_handle(), mask);
}