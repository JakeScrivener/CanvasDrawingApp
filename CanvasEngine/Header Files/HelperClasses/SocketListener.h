#pragma once
#include "SocketStreamer.h"

class Listener : public Socket
{
	SOCKET mListener;
	std::shared_ptr<NetworkManager> mNetworkManager = NetworkManager::Instance();

public:
	Listener(const IPAddress& pIp);
	~Listener();

	void Listen();

};

