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
	//BIO_dump_fp(stdout, reinterpret_cast<char*>(&Data->Packet.Request), Data->Size);
	this->Service->CMDLayer->Receive(Data);
}



void DNDataLayer::Send(DNTransData *Data)
{
	if (Data->EncryptType == DNEncryptType::RSA)
	{
		this->__RSAEncryptData(Data, this->Service->Config->LocalPubKey);
	}
	//BIO_dump_fp(stdout, reinterpret_cast<char*>(&Data->Packet.Request), Data->Size);
	this->Service->PacketLayer->Send(Data);
}



void DNDataLayer::__RSAEncryptData(DNTransData *Data, EVP_PKEY* RSAKey)
{
	const int Encrypt_Block_Size = this->Service->Config->Key_Bits / 8 - 42;
	unsigned char* __Dest = new unsigned char[DNPacketLength];
	size_t __DestSize = DNPacketLength;
	size_t __OriSize = Data->Size;
	Data->Size = 0;
	for (int i = 0; i < __OriSize; i += Encrypt_Block_Size)
	{
		int size = min(i + Encrypt_Block_Size, __OriSize) - i;
		size_t ___DestSize = __DestSize - Data->Size;
		unsigned char* ___Dest = __Dest + Data->Size;
		DCryptRSA::EVP_Encrypt(RSAKey, ___Dest, ___DestSize, reinterpret_cast<unsigned char*>(&Data->Packet.Request) + i, size);
		Data->Size += ___DestSize;
	}
	memcpy(reinterpret_cast<char*>(&Data->Packet.Request), __Dest, Data->Size);
	delete[]__Dest;
}

void DNDataLayer::__RSADecryptData(DNTransData *Data, EVP_PKEY* RSAKey)
{
	const int Decrypt_Block_Size = this->Service->Config->Key_Bits / 8;
	unsigned char* __Dest = new unsigned char[DNPacketLength];
	size_t __DestSize = DNPacketLength;
	size_t __OriSize = Data->Size;
	Data->Size = 0;
	for (int i = 0; i < __OriSize; i += Decrypt_Block_Size)
	{
		int size = min(i + Decrypt_Block_Size, __OriSize) - i;
		size_t ___DestSize = __DestSize - Data->Size;
		unsigned char* ___Dest = __Dest + Data->Size;
		DCryptRSA::EVP_Decrypt(RSAKey, ___Dest, ___DestSize, reinterpret_cast<unsigned char*>(&Data->Packet.Request) + i, size);
		Data->Size += ___DestSize;
	}
	memcpy(reinterpret_cast<char*>(&Data->Packet.Request), __Dest, Data->Size);

	delete[]__Dest;
}


