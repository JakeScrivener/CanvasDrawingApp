#pragma once
#include <vector>
#include <string>
#include <queue>
#include "ThreadManager.h"
#include <iostream>
#include <fstream>
#include "AntTweakManager.h"
#include <array>
#include "FrequencyValues.h"

class Listener;
class Peer;

class NetworkManager
{
private:
	NetworkManager();

	std::shared_ptr<ThreadManager> mThreadManager = ThreadManager::Instance();
	std::shared_ptr<AntTweakManager> mAntTweakManager = AntTweakManager::Instance();
	//message queue
	std::queue<std::string> mSendQueue;
	std::queue<std::string> mFlushQueue;
	std::queue<std::string> mReceivedQueue;

	//must be ptr due to forward declarations
	Listener* mListener;
	std::vector<Peer*> mStreamers;

	std::string mTerminator = "*JS*";
	std::mutex mx;

	std::vector<int> mCore2;
	std::vector<int> mCore3plus;

	std::chrono::nanoseconds mDeltaTime{};
	std::chrono::high_resolution_clock::time_point mStartTime;
	std::chrono::high_resolution_clock::time_point mCurrentTime;
	std::chrono::high_resolution_clock::time_point mPreviousTime;
	int mActualFrequency{};
	double mAverageDeltaTime = 0;
	double mTargetDeltaTime = 0;
	std::array<double, 50> mLast50Frames{};
	double mSleepTime{};

	void CalculateFreq();
	void Broadcast();
	void FlushQueue();

public:

	~NetworkManager();
	void Init();


	void AddStreamer(Peer* pStreamer);
	void RemoveStreamer(Peer* pStreamer);
	void AddMessage(const std::string& pMessage);
	void AddResponse(const std::string& pMessage);
	void SinglePeerFlush(void* pPeer, void* pQueue);
	std::queue<std::string> ReceivedMessages();
	int Connections() const;

	//Singleton pattern
	//Deleted copy constructor and assignment operator so no copies of the singleton instance can be made
	NetworkManager(const NetworkManager&) = delete;
	NetworkManager& operator=(const NetworkManager&) = delete;

	static std::shared_ptr<NetworkManager> Instance();
};
