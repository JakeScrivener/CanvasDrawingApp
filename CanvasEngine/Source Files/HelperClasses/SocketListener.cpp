#include "SocketListener.h"


Listener::Listener(const IPAddress& pIp) : Socket(pIp)
{
	mPeer.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	mListener = socket(AF_INET, SOCK_STREAM, 0);
	if (mListener == INVALID_SOCKET)
	{
		OutputDebugString(L"Create Socket Failed");
		OutputDebugString(L"\n");
	}
	else
	{
		while (bind(mListener, reinterpret_cast<sockaddr*>(&mPeer), sizeof(mPeer)) == SOCKET_ERROR)
		{
			OutputDebugString(L"Bind Failed with ");
			OutputDebugString(std::to_wstring(WSAGetLastError()).c_str());
			OutputDebugString(L"\n");
			mPeer.sin_port = mPeer.sin_port + 1;
		}
		if (listen(mListener, 5) == SOCKET_ERROR)
		{
			OutputDebugString(L"Listen Failed with ");
			OutputDebugString(std::to_wstring(WSAGetLastError()).c_str());
			OutputDebugString(L"\n");
		}
		else
		{
			OutputDebugString(L"Listening\n");
		}
	}
}


Listener::~Listener() = default;

void Listener::Listen()
{
	while (true)
	{
		mTransfer = SOCKET_ERROR;
		while (mTransfer == SOCKET_ERROR)
		{
			mTransfer = accept(mListener, nullptr, nullptr);
		}
		if (mTransfer == INVALID_SOCKET)
		{
			OutputDebugString(L"Accept Failed with ");
			OutputDebugString(std::to_wstring(WSAGetLastError()).c_str());
			OutputDebugString(L"\n");
		}
		else
		{
			//Create new streamer on thread
			const auto peer = new Peer(mTransfer);

			//Add streamer to network manager
			mNetworkManager->AddStreamer(peer);
		}
	}
}
