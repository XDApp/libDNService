#include "stdafx.h"
#include "DNNetworkLayer.h"
#include "DNServiceManager.h"
#include "DNUserLayer.h"
#include "DNPacket.h"
#include "DNCmd.h"

DNNetworkLayer::DNNetworkLayer(DNServiceManager *service) :DNLayer(service)
{
}


DNNetworkLayer::~DNNetworkLayer()
{
}

void DNNetworkLayer::Receive(DNTransData *Data)
{
	this->Service->PacketLayer->Receive(Data);
}

void DNNetworkLayer::Send(DNTransData *Data)
{
	//while (!this->Service->SocketLock.try_lock())Sleep(50);
	this->Service->ListenSocket->Send((const char*)(&Data->Packet), Data->Size + 10, Data->Addr);
	//this->Service->SocketLock.unlock();
	this->DestroyPacket(Data);
}
