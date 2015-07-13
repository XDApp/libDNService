#include "stdafx.h"
#include "DNDataLayer.h"
#include "DNServiceManager.h"
#include "DNPacket.h"
#include "DNConfigManager.h"

DNDataLayer::DNDataLayer(DNServiceManager *service) :DNLayer(service)
{
}


DNDataLayer::~DNDataLayer()
{
}

void DNDataLayer::Receive(DNTransData *Data)
{
	if (Data->EncryptType == DNEncryptType::RSA)
	{
		this->__RSADecryptData(Data, this->Service->Config->LocalPriKey);
	}
	this->Service->CMDLayer->Receive(Data);
}



void DNDataLayer::Send(DNTransData *Data)
{
	if (Data->EncryptType == DNEncryptType::RSA)
	{
		this->__RSAEncryptData(Data, this->Service->Config->LocalPubKey);
	}
	this->Service->PacketLayer->Send(Data);
}

void DNDataLayer::__RSAEncryptData(DNTransData *Data, EVP_PKEY* RSAKey)
{
	unsigned char* __Dest = new unsigned char[DNPacketLength];
	size_t __DestSize = DNPacketLength;

	DCryptRSA::EVP_Encrypt(RSAKey, __Dest, __DestSize, reinterpret_cast<unsigned char*>(&Data->Packet.Request), Data->Size);

	Data->Size = __DestSize;
	memcpy(reinterpret_cast<char*>(&Data->Packet.Request), reinterpret_cast<char*>(__Dest), __DestSize);

	delete[]__Dest;
}

void DNDataLayer::__RSADecryptData(DNTransData *Data, EVP_PKEY* RSAKey)
{
	unsigned char* __Dest = new unsigned char[DNPacketLength];
	size_t __DestSize = DNPacketLength;
	size_t __OriSize = Data->Size;

	DCryptRSA::EVP_Decrypt(RSAKey, __Dest, __DestSize, reinterpret_cast<unsigned char*>(&Data->Packet.Request), Data->Size);

	Data->Size = __DestSize;
	memcpy(reinterpret_cast<char*>(&Data->Packet.Request), reinterpret_cast<char*>(__Dest), __DestSize);

	delete[]__Dest;
}


