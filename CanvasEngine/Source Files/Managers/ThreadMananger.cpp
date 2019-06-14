#include "ThreadManager.h"
#include "Thread.h"
#include <mutex>

ThreadManager::ThreadManager()
{
	mThreadCount = std::thread::hardware_concurrency() * 2;
}

ThreadManager::~ThreadManager()
{
	DeleteThreads();
}

/// <summary>
/// Gets a pointer to the next task in the queue and removes it from the queue
/// </summary>
/// <returns> the next task to execute </returns>
Task ThreadManager::GetTask()
{
	std::lock_guard<std::mutex> lg(mx);
	if (mTodo.empty())
	{
		std::vector<int> emptyVec;
		return Task(nullptr, nullptr, nullptr, emptyVec);
	}

	const auto task = mTodo.front();
	mTodo.pop();
	return task;
}

/// <summary>
/// Adds a task to the todo list
/// </summary>
/// <param name="pFunction"> the function which needs to be executed </param>
/// <param name="pCore"> the core that the task should execute on </param>
void ThreadManager::AddTask(std::function<void(void*, void*)> pFunction, void* pData1, void* pData2, const std::vector<int>& pCores)
{
	std::lock_guard<std::mutex> lg(mx);
	mTodo.emplace(pFunction, pData1, pData2, pCores);
}

/// <summary>
///  Returns a boolean true if the task is complete and removes it from the done list else return false
/// </summary>
/// <param name="pFunction"> the function which must be checked if complete </param>
/// <returns> boolean true if the function has completed execution </returns>
bool ThreadManager::TaskComplete(std::function<void(void*, void*)> pFunction)
{
	std::lock_guard<std::mutex> lg(mx);
	const auto foundPos = std::find_if(mDone.begin(), mDone.end(), [&] (std::function<void(void*, void*)> pDoneFunction) { return (&pFunction == &pDoneFunction);	});
	if (foundPos != mDone.end())
	{
		mDone.erase(foundPos);
	}
	return (foundPos != mDone.end());
}

/// <summary>
/// Marks the given task a complete
/// </summary>
/// <param name="pFunction"> the function which has been completed</param>
void ThreadManager::CompleteTask(std::function<void(void*, void*)> pFunction)
{
	std::lock_guard<std::mutex> lg(mx);
	mDone.push_back(pFunction);
}

bool ThreadManager::TasksQueued()
{
	std::lock_guard<std::mutex> lg(mx);
	return !mTodo.empty();
}

/// <summary>
/// Creates the maximum number of threads
/// </summary>
void ThreadManager::CreateThreads()
{
	for (int i = 0; i < mThreadCount; ++i)
	{
		mThreads.emplace(new Thread(i));
	}
}

/// <summary>
/// Deletes the threads
/// </summary>
void ThreadManager::DeleteThreads()
{
	for (int i = 0; i < mThreadCount; ++i)
	{
		delete mThreads.front();
		mThreads.pop();
	}
}

/// <summary>
/// returns an instance of the thread manager
/// </summary>
/// <returns>instance of thread manager</returns>
std::shared_ptr<ThreadManager> ThreadManager::Instance()
{
	static std::shared_ptr<ThreadManager> instance{ new ThreadManager };
	return instance;
}
