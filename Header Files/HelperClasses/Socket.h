#pragma once
#include <WinSock2.h>
#include "IPAddress.h"

class Socket
{
protected:
	sockaddr_in mPeer;
	IPAddress mIp;
	SOCKET mTransfer;
public:
	Socket(const IPAddress& pIp);
	~Socket();
};

