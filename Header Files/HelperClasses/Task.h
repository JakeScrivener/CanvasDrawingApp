#pragma once
#include <functional>
#include <vector>

class Task
{
private:
	std::function<void(void*, void*)> mFunction;
	void* mData1;
	void* mData2;
	std::vector<int> mCores;

public:
	Task(std::function<void(void*, void*)> pFunction, void* pData1, void* pData2, std::vector<int> pCores);
	~Task();

	std::function<void(void*, void*)> Function() const;
	std::pair<void*, void*> Data();
	std::vector<int> Cores() const;
};
