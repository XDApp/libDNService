#pragma once
#include "DNCmd.h"

class DNCmdEcho :
	public DNCmd
{
	DClass(DNCmdEcho)
public:
	DNCmdEcho(DNServiceManager* service);
	~DNCmdEcho();
	virtual void Send(const DSocketAddrIn &Addr);
	virtual void Recv(DNTransData* Data);
};

class DNCmdEchoReply :
	public DNCmd
{
	DClass(DNCmdEchoReply)
public:
	DNCmdEchoReply(DNServiceManager* service);
	~DNCmdEchoReply();
	virtual void Send(const DSocketAddrIn &Addr);
	virtual void Recv(DNTransData* Data);

	DEventManager *WhenRecv;
};

