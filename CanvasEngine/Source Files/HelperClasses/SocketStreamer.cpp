#include "SocketStreamer.h"

Peer::Peer(const IPAddress& pIp) : Socket(pIp), mTerminator("*JS*"), mMessagesFailed(0)
{
	inet_pton(mPeer.sin_family, mIp.Address().c_str(), &mPeer.sin_addr);
	mTransfer = socket(AF_INET, SOCK_STREAM, 0);
}

Peer::Peer(const SOCKET & pSocket) : Socket(IPAddress("", 0)), mTerminator("*JS*"), mMessagesFailed(0)
{
	mTransfer = pSocket;
}


Peer::~Peer() = default;

void Peer::Send(const std::string& pMessage) const
{
	if (send(mTransfer, pMessage.c_str(), pMessage.length(), 0) == SOCKET_ERROR)
	{
		OutputDebugString(L"Send failed with ");
		OutputDebugString(std::to_wstring(WSAGetLastError()).c_str());
		OutputDebugString(L"\n");
	}
	//OutputDebugString(L"Message sent\n");
}

bool Peer::Connect()
{
	if (mTransfer == INVALID_SOCKET)
	{
		OutputDebugString(L"Create Socket Failed");
		OutputDebugString(std::to_wstring(WSAGetLastError()).c_str());
		OutputDebugString(L"\n");
		return false;
	}
	if (connect(mTransfer, reinterpret_cast<sockaddr*>(&mPeer), sizeof(mPeer)) == SOCKET_ERROR)
	{
		OutputDebugString(L"Connect to peer failed with ");
		OutputDebugString(std::to_wstring(WSAGetLastError()).c_str());
		OutputDebugString(L"\n");
		return false;
	}
	OutputDebugString(L"Connected\n");
	return true;
}

void Peer::Listen()
{
	while (true)
	{
		std::vector<char> buffer;
		char c;
		int totalBytes = 0;
		int receivedBytes;
		std::string terminator;
		mMessagesFailed = 0;
		//receive message
		while (terminator != mTerminator)
		{
			terminator = "";
			if (mMessagesFailed > 5)
			{
				mNetworkManager->RemoveStreamer(this);
				return;
			}
			if ((receivedBytes = recv(mTransfer, &c, 1, 0)) == SOCKET_ERROR)
			{
				OutputDebugString(L"Receive Failed with ");
				OutputDebugString(std::to_wstring(WSAGetLastError()).c_str());
				OutputDebugString(L"\n");
				mMessagesFailed++;
			}
			else
			{
				//OutputDebugString(L"Receiving Message\n");
				totalBytes += receivedBytes;
				buffer.push_back(c);
				if (buffer.size() >= 4)
				{
					terminator += buffer[totalBytes - 4];
					terminator += buffer[totalBytes - 3];
					terminator += buffer[totalBytes - 2];
					terminator += buffer[totalBytes - 1];
				}
			}
		}
		for (int i = 0; i < 4; ++i)
		{
			buffer.pop_back();
		}
		buffer.push_back('\0');

		std::lock_guard<std::mutex> lg(mx);
		mNetworkManager->AddResponse(&buffer.front());
	}
}
