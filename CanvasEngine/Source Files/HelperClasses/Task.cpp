#include "Task.h"
#include <utility>

using namespace std;

Task::Task(std::function<void(void*, void*)> pFunction, void * pData1, void * pData2, std::vector<int> pCores) : mFunction(std::move(pFunction)), mData1(pData1), mData2(pData2), mCores(std::move(pCores))
{
}

Task::~Task()
{
}

std::function<void(void*, void*)> Task::Function() const
{
	return mFunction;
}

std::pair<void*, void*> Task::Data()
{
	return make_pair(mData1, mData2);
}

std::vector<int> Task::Cores() const
{
	return mCores;
}
