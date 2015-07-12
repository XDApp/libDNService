#pragma once

#include "DNPacket.h"
#include "DNServiceManager.h"
#include "DNLayer.h"

class DSocketAddrIn;

enum class DNCmdType : DNCommand
{
	Echo = 0,
	ReplyEcho,
	Token,
	ReplyToken
};

class DNCmd
	: public DObject
{
	DClass(DNCmd)
protected:
	DNServiceManager* Service;
public:
	DNCmd(DNServiceManager* service);
	~DNCmd();
	virtual void Send(const DSocketAddrIn &Addr);
	virtual void Recv(DNTransData* Data);

	DNTransData* CreatePacket();
	void DestroyPacket(DNTransData *Data);
};

