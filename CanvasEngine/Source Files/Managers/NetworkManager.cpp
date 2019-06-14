#include "SocketListener.h"
#include "../../../CanvasGame/Header Files/Systems/NetworkUpdateSystem.h"
#pragma comment(lib, "Ws2_32.lib")

NetworkManager::NetworkManager() : mListener(nullptr), mDeltaTime(0)
{
	const auto wVersionRequested = MAKEWORD(2, 0);
	WSADATA wsaData;
	if (WSAStartup(wVersionRequested, &wsaData))
	{
		OutputDebugString(L"Socket initialisation failed");
	}
	FrequencyValues::gNetFreq = 10;
	mAntTweakManager->AddWritableVariable("Stats", "Target Network Freq", FrequencyValues::gNetFreq, "group = Networking min=1 max=120");
	mAntTweakManager->AddVariable("Stats", "Actual Network Freq", mActualFrequency, "group = Networking min=1 max=120");

	const int cores = std::thread::hardware_concurrency();
	for (int i = 3; i < cores; ++i)
	{
		mCore3plus.push_back(i);
	}

	mCore2.push_back(2);
}

/// <summary>
/// Delete all socket objects and clean up windows socket adapters
/// </summary>
NetworkManager::~NetworkManager()
{
	delete mListener;
	for (auto streamer : mStreamers)
	{
		delete streamer;
	}
	WSACleanup();
}

/// <summary>
/// Initialise the network manager when called after construction
/// </summary>
void NetworkManager::Init()
{
	//perform initial broadcast to find other players (using ip addresses found in the config file - can replace with udp broadcast)
	Broadcast();

	//Create listener to wait for other players to connect
	mListener = new Listener(IPAddress("", 9171));//Port 9171-9176 may be used - 9171 listener, 9172+ peers
	//Listen on thread
	mThreadManager->AddTask(std::bind(&Listener::Listen, mListener), nullptr, nullptr, mCore2);

	//Begin flush cycle
	mThreadManager->AddTask(std::bind(&NetworkManager::FlushQueue, this), nullptr, nullptr, mCore2);
}

void NetworkManager::CalculateFreq()
{
	// Average the fps over n frames.
	mAverageDeltaTime = 0;
	for (auto i = 0; i < static_cast<int>(mLast50Frames.size() - 1); i++)
	{
		mLast50Frames[i] = mLast50Frames[i + 1];
	}
	mLast50Frames[mLast50Frames.size() - 1] = mDeltaTime.count() / pow(10, 9);

	for (auto frame : mLast50Frames)
	{
		mAverageDeltaTime += frame;
	}
	mAverageDeltaTime = mAverageDeltaTime / mLast50Frames.size();

	mActualFrequency = static_cast<int>(1 / (mDeltaTime.count() / pow(10, 9)));

	mTargetDeltaTime = 1.0 / FrequencyValues::gNetFreq;
	mSleepTime += mTargetDeltaTime - mDeltaTime.count() / pow(10, 9);


}

/// <summary>
/// Broadcasts using TCP to all IPs in the given config file to see if the players are there
/// then sets up sockets for active connections
/// </summary>
void NetworkManager::Broadcast()
{
	//Read target addresses from config file
	std::ifstream fin("config.txt", std::ifstream::in);

	std::vector<std::string> hosts;
	std::vector<std::string> ports;
	while (!fin.eof())
	{
		std::string host;
		std::getline(fin, host);
		hosts.push_back(host);

		std::string port;
		std::getline(fin, port);
		ports.push_back(port);
	}

	fin.close();


	for (auto i = 0; i < static_cast<int>(hosts.size()); ++i)
	{
		auto peer = new Peer(IPAddress(hosts[i], std::stoi(ports[i])));
		if (peer->Connect())
		{
			auto msg = std::to_string(i + 1) + ":C" + mTerminator;
			peer->Send(msg);
			AddStreamer(peer);
		}
		else
		{
			delete peer;
		}
	}
}

/// <summary>
/// Adds a socket streamer / peer
/// </summary>
/// <param name="pStreamer"> a pointer to the socketstreamer to be added to the managers list </param>
void NetworkManager::AddStreamer(Peer * pStreamer)
{
	mStreamers.push_back(pStreamer);
	mThreadManager->AddTask(std::bind(&Peer::Listen, pStreamer), nullptr, nullptr, mCore3plus);
}

void NetworkManager::RemoveStreamer(Peer * pStreamer)
{
	delete pStreamer;
	mStreamers.erase(std::remove_if(mStreamers.begin(), mStreamers.end(), [&](Peer* peer) { return (peer == pStreamer); }), mStreamers.end());
	//Send a reset to everyone (+ reset itself)
	AddMessage("0:R");
}

/// <summary>
/// Adds a message to the list of messages to send
/// </summary>
/// <param name="pMessage"> The message to add </param>
void NetworkManager::AddMessage(const std::string & pMessage)
{
	std::lock_guard<std::mutex> lg(mx);
	mSendQueue.emplace(pMessage + mTerminator);
}
/// <summary>
/// Adds a received message to the received queue
/// </summary>
/// <param name="pMessage"> the message to add </param>
void NetworkManager::AddResponse(const std::string & pMessage)
{
	std::lock_guard<std::mutex> lg(mx);
	mReceivedQueue.emplace(pMessage);
}

/// <summary>
/// Loops creating tasks to flush the entire send queue to each peer
/// </summary>
void NetworkManager::FlushQueue()
{
	mCurrentTime = std::chrono::high_resolution_clock::now();
	while (true)
	{
		mPreviousTime = mCurrentTime;

		int peerCount;
		{ //lock
			std::lock_guard<std::mutex> lg(mx);
			mFlushQueue.swap(mSendQueue);
			peerCount = mStreamers.size();
		}

		if (peerCount > 0)
		{
			for (int i = 0; i < peerCount; ++i)
			{
				auto* peerQueue = new std::queue<std::string>(mFlushQueue);
				mThreadManager->AddTask(std::bind(&NetworkManager::SinglePeerFlush, this, std::placeholders::_1, std::placeholders::_2), mStreamers[i], peerQueue, mCore3plus);
			}
		}

		//clear queue
		{ //lock
			std::lock_guard<std::mutex> lg(mx);
			std::queue<std::string> emptyQueue;
			mFlushQueue.swap(emptyQueue);
		}

		mCurrentTime = std::chrono::high_resolution_clock::now();
		mDeltaTime = mCurrentTime - mPreviousTime;
		CalculateFreq();
		if (mSleepTime > 0)
			Sleep(mSleepTime * 1000);


	}
}

/// <summary>
/// Flushes the given queue to the given peer
/// </summary>
/// <param name="pPeer"> The peer to send the messages to </param>
/// <param name="pQueue"> The queue to send </param>
void NetworkManager::SinglePeerFlush(void* pPeer, void* pQueue)
{
	auto* peer = static_cast<Peer*>(pPeer);
	auto* queue = static_cast<std::queue<std::string>*>(pQueue);

	//Send all messages to all peers
	while (!queue->empty())
	{
		peer->Send(queue->front());
		queue->pop();
	}

	delete queue;
}

/// <summary>
/// Returns the list of messages that have been received and clears the received queue
/// </summary>
/// <returns> queue of messages received </returns>
std::queue<std::string> NetworkManager::ReceivedMessages()
{
	std::queue<std::string>  emptyQueue;
	std::lock_guard<std::mutex> lg(mx);
	if (!mReceivedQueue.empty())
	{
		mReceivedQueue.swap(emptyQueue);
	}
	return emptyQueue;
}

/// <summary>
/// Returns a count of peer connections currently existing
/// </summary>
/// <returns> int number of peers </returns>
int NetworkManager::Connections() const
{
	return mStreamers.size();
}

/// <summary>
/// Gets an instance of the network manager in singleton pattern
/// </summary>
/// <returns> static instance of network manager </returns>
std::shared_ptr<NetworkManager> NetworkManager::Instance()
{
	static std::shared_ptr<NetworkManager> instance{ new NetworkManager };
	return instance;
}

