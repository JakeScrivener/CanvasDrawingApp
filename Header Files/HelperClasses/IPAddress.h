#pragma once
#include <string>

class IPAddress
{
	std::string mAddress;
	int mPort;

public:
	IPAddress(const std::string& pAddress, const int& pPort);
	~IPAddress();

	const std::string& Address() const { return mAddress; }
	void Address(const std::string& pAddress) { mAddress = pAddress; }
	const int& Port() const { return mPort; }
	void Port(const int& pPort) { mPort = pPort; }
};

