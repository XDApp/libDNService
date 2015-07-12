#include "stdafx.h"
#include "DNPacketLayer.h"
#include "DNServiceManager.h"

DNPacketLayer::DNPacketLayer(DNServiceManager *service) :DNLayer(service)
{
}


DNPacketLayer::~DNPacketLayer()
{
}

void DNPacketLayer::Receive(DNTransData *Data)
{
	Data->Size -= sizeof(Data->Size) + sizeof(Data->EncryptType);
	this->Service->DataLayer->Receive(Data);
}

void DNPacketLayer::Send(DNTransData *Data)
{
	Data->Size += sizeof(Data->Size) + sizeof(Data->EncryptType);
	this->Service->NetworkLayer->Send(Data);
}
