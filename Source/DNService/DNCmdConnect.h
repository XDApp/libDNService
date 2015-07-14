#pragma once
#include "DNCmd.h"

class DNServiceManager;
class DEventManager;

class DNCmdConnect :
	public DNCmd
{
	DClass(DNCmdConnect)
public:
	DNCmdConnect(DNServiceManager* service);
	~DNCmdConnect();
	virtual void Send(const DSocketAddrIn &Addr) override;
	virtual void Recv(DNTransData* Data) override;
};

class DNCmdConnectReply :
	public DNCmd
{
	DClass(DNCmdConnectReply)
public:
	DNCmdConnectReply(DNServiceManager* service);
	~DNCmdConnectReply();
	virtual void Send(const DSocketAddrIn &Addr) override;
	virtual void Recv(DNTransData* Data) override;

	DEventManager *WhenRecv;
};
