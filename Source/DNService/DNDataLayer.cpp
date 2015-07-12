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

EVP_PKEY *___Data_TMP_Key;

void DNDataLayer::Receive(DNTransData *Data)
{
	if (Data->EncryptType == DNEncryptType::RSA)
	{
		this->__RSADecryptData(Data, ___Data_TMP_Key);
	}
	this->Service->CMDLayer->Receive(Data);
}



void DNDataLayer::Send(DNTransData *Data)
{
	if (Data->EncryptType == DNEncryptType::RSA)
	{
		this->__RSAEncryptData(Data, ___Data_TMP_Key);
	}
	this->Service->PacketLayer->Send(Data);
}

void DNDataLayer::__RSAEncryptData(DNTransData *Data, EVP_PKEY* RSAKey)
{
	unsigned char* __Dest;
	size_t __DestSize = DNPacketLength;

	DCryptRSA::EVP_Encrypt(RSAKey, __Dest, __DestSize, reinterpret_cast<unsigned char*>(&Data->Packet.Request), Data->Size);

	Data->Size = __DestSize;
	memcpy(Data->Data, (const char*)__Dest, __DestSize);

	OPENSSL_free(__Dest);
}

void DNDataLayer::__RSADecryptData(DNTransData *Data, EVP_PKEY* RSAKey)
{
	unsigned char* __Dest;
	size_t __DestSize = DNPacketLength;
	size_t __OriSize = Data->Size;

	DCryptRSA::EVP_Decrypt(RSAKey, __Dest, __DestSize, reinterpret_cast<unsigned char*>(Data->Data), Data->Size);

	Data->Size = __DestSize;
	memcpy(reinterpret_cast<char*>(&Data->Packet.Request), (char*)__Dest, __DestSize);

	OPENSSL_free(__Dest);
}


