#pragma once
#include "DNCmd.h"

class DNCmdToken :
	public DNCmd
{
	DClass(DNCmdToken)
public:
	DNCmdToken(DNServiceManager* service);
	~DNCmdToken();
	virtual void Send(const DSocketAddrIn &Addr);
	virtual void Recv(DNTransData* Data);
};

class DNCmdTokenReply :
	public DNCmd
{
	DClass(DNCmdTokenReply)
public:
	DNCmdTokenReply(DNServiceManager* service);
	~DNCmdTokenReply();
	virtual void Send(const DSocketAddrIn &Addr);
	virtual void Recv(DNTransData* Data);

	DEventManager *WhenRecv;
};

