#include "stdafx.h"
#include "DNCmdConnect.h"
#include "DNServiceManager.h"
#include "DNCmdProcessor.h"
#include "DNConfigManager.h"

DNCmdConnect::DNCmdConnect(DNServiceManager* service) :DNCmd(service)
{
}


DNCmdConnect::~DNCmdConnect()
{
}

DNCmdConnectReply::DNCmdConnectReply(DNServiceManager* service) 
	: DNCmd(service),
	WhenRecv(new DEventManager())
{
}


DNCmdConnectReply::~DNCmdConnectReply()
{
	DDel(WhenRecv);
}

void DNCmdConnect::Send(const DSocketAddrIn &Addr)
{
	DNTransData *Data = this->CreatePacket();
	Data->EncryptType = DNEncryptType::None;
	Data->Addr = Addr;
	Data->Cmd = (DNCommand)DNCmdType::Connect;
	Data->Size = 0;
	this->Service->UserLayer->Send(Data);
}

void DNCmdConnect::Recv(DNTransData* Data)
{
	DNCmdConnectReply *Cmd = this->Service->Processor->ParseCmd<DNCmdConnectReply>(DNCmdType::ReplyConnect);
	Cmd->Send(Data->Addr);
}


void DNCmdConnectReply::Send(const DSocketAddrIn &Addr)
{
	DNTransData *Data = this->CreatePacket();

	Data->EncryptType = DNEncryptType::None;
	Data->Addr = Addr;
	Data->Cmd = (DNCommand)DNCmdType::ReplyConnect;

	unsigned char *_Key = reinterpret_cast<unsigned char*>(Data->Data);
	int _len = i2d_RSAPublicKey(this->Service->Config->LocalPubRSAKey, &_Key);
	Data->Size = _len;

	this->Service->UserLayer->Send(Data);
}

void DNCmdConnectReply::Recv(DNTransData* Data)
{
	unsigned char *_Key = reinterpret_cast<unsigned char*>(Data->Data);
	this->Service->Config->LocalPubKey = DCryptRSA::ToEVP(d2i_RSAPublicKey(nullptr, const_cast<const unsigned char**>(&_Key), Data->Size));
	this->WhenRecv->Call(Data);
}

