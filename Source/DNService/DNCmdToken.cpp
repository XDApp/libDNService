#include "stdafx.h"
#include "DNCmdToken.h"
#include "DNPacket.h"
#include "DNServiceManager.h"
#include "DNCmdProcessor.h"

DNCmdToken::DNCmdToken(DNServiceManager* service) :DNCmd(service)
{
}


DNCmdToken::~DNCmdToken()
{
}

void DNCmdToken::Send(const DSocketAddrIn &Addr)
{
	DNTransData *Data = this->CreatePacket();
	Data->EncryptType = DNEncryptType::RSA;
	Data->Addr = Addr;
	Data->Cmd = (DNCommand)DNCmdType::Token;
	Data->Size = 0;
	this->Service->UserLayer->Send(Data);
}

void DNCmdToken::Recv(DNTransData* Data)
{
	DNCmdTokenReply *Cmd = this->Service->Processor->ParseCmd<DNCmdTokenReply>(DNCmdType::ReplyToken);
	Cmd->Send(Data->Addr);
}

DNCmdTokenReply::DNCmdTokenReply(DNServiceManager* service)
	:DNCmd(service),
	WhenRecv(new DEventManager())
{
}


DNCmdTokenReply::~DNCmdTokenReply()
{
	DDel(WhenRecv);
}

const int TokenSize = 1068;

void DNCmdTokenReply::Send(const DSocketAddrIn &Addr)
{
	DNTransData *Data = this->CreatePacket();

	Data->EncryptType = DNEncryptType::RSA;
	Data->Addr = Addr;
	Data->Cmd = (DNCommand)DNCmdType::ReplyToken;

	for (int i = 0; i < TokenSize; i++)
	{
		int _char = rand() % 36;
		char &_Target = Data->Data[i];
		if (_char < 10)_Target = static_cast<char>(_char + '0');
		else if (_char >= 10)_Target = static_cast<char>(_char + 'a' - 10);
	}
	Data->Size = TokenSize;

	this->Service->UserLayer->Send(Data);
}

void DNCmdTokenReply::Recv(DNTransData* Data)
{
	this->WhenRecv->Call(Data);
}

