#include "Socket.h"

using namespace std;

Socket::Socket(const IPAddress& pIp) : mIp(pIp)
{
	mPeer.sin_family = AF_INET;
	mPeer.sin_port = mIp.Port();
}

Socket::~Socket()
{

}

