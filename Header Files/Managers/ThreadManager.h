#pragma once
#include <vector>
#include <queue>
#include <mutex>
#include "Task.h"

class Thread;

class ThreadManager
{
private:
	ThreadManager();

	//Thread Pool
	std::queue<Thread*> mThreads;
	std::queue<Task> mTodo; // function to be executed paired with the core to execute on
	std::vector<std::function<void(void*, void*)>> mDone; // functions which have finished executing
	int mThreadCount;
	void DeleteThreads();
	std::mutex mx;

public:
	void CreateThreads();
	~ThreadManager();

	//Singleton pattern
	//Deleted copy constructor and assignment operator so no copies of the singleton instance can be made
	ThreadManager(const ThreadManager&) = delete;
	ThreadManager& operator=(const ThreadManager&) = delete;

	Task GetTask();
	void AddTask(std::function<void(void*, void*)> pFunction, void* pData1, void* pData2, const std::vector<int>& pCores);

	bool TaskComplete(std::function<void(void*, void*)> pFunction);
	void CompleteTask(std::function<void(void*, void*)> pFunction);
	bool TasksQueued();

	static std::shared_ptr<ThreadManager> Instance();
};
