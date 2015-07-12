#pragma once
#include "DNCmd.h"

class DNServiceManager;

class DNCmdConnect :
	public DNCmd
{
	DClass(DNCmdConnect)
public:
	DNCmdConnect(DNServiceManager* service);
	~DNCmdConnect();
	virtual void Send(const DSocketAddrIn &Addr) = 0;
	virtual void Recv(DNTransData* Data) = 0;
};

class DNCmdConnectReply :
	public DNCmd
{
	DClass(DNCmdConnectReply)
public:
	DNCmdConnectReply(DNServiceManager* service);
	~DNCmdConnectReply();
	virtual void Send(const DSocketAddrIn &Addr) = 0;
	virtual void Recv(DNTransData* Data) = 0;
};
