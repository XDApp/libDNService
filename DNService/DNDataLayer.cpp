#include "stdafx.h"
#include "DNDataLayer.h"
#include "DNServiceManager.h"
#include "DNPacket.h"
DNDataLayer::DNDataLayer(DNServiceManager *service) :DNLayer(service)
{
}


DNDataLayer::~DNDataLayer()
{
}

void DNDataLayer::Receive(DNTransData *Data)
{
	//DecryptData(Data);
	this->Service->CMDLayer->Receive(Data);
}

void DNDataLayer::Send(DNTransData *Data)
{
	//EncryptData(Data);
	this->Service->PacketLayer->Send(Data);
}

void DNDataLayer::EncryptData(DNTransData *Data)
{
	char ori[DNPacketLength];
	strncpy_s(ori, Data->Data, Data->Size);
	int _oSize = Data->Size;
	Data->Size = DNRequestLength - 2;
}

void DNDataLayer::DecryptData(DNTransData *Data)
{
	char ori[DNPacketLength];
	strncpy_s(ori, Data->Data, Data->Size);
	int _oSize = Data->Size;
}


