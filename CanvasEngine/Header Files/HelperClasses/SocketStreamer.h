#pragma once
#include "NetworkManager.h"
#include "Socket.h"
#include <ws2tcpip.h>
#include <vector>

class Peer : public Socket
{

	std::shared_ptr<NetworkManager> mNetworkManager = NetworkManager::Instance();
	std::string mTerminator;

	std::mutex mx;

	int mMessagesFailed;

public:
	Peer(const IPAddress& pIp);
	Peer(const SOCKET& pSocket);
	~Peer();

	void Send(const std::string& pMessage) const;
	bool Connect();
	void Listen();
};

