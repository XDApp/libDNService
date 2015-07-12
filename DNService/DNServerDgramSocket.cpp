#include "stdafx.h"
#include "DNServerDgramSocket.h"


DNServerDgramSocket::DNServerDgramSocket()
{
	int iMode = 1;
	ioctlsocket(this->sock, FIONBIO, (u_long FAR*) &iMode);
	int nRecvBufLen = 1024 * 1024 * 16;
	setsockopt(this->sock, SOL_SOCKET, SO_RCVBUF, (const char*)&nRecvBufLen, sizeof(int));
}


DNServerDgramSocket::~DNServerDgramSocket()
{
}
