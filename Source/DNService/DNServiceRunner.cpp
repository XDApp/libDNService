#include "stdafx.h"
#include "DNServiceManager.h"
#include "DNNetworkLayer.h"
#include "DNDataLayer.h"
#include "DNPacketLayer.h"
#include "DNCmdLayer.h"
#include "DNUserLayer.h"
#include "DSocketSystem.h"

#include "DNCmdProcessor.h"
#include "DNCmdEcho.h"
#include "DNCmdToken.h"

#include "DNServiceRunner.h"
#include "DNServerDgramSocket.h"
#include "DNConfigManager.h"

DNServiceRunner::DNServiceRunner(DNConfigManager *Config)
	: config(Config)
{
}


DNServiceRunner::~DNServiceRunner()
{
}

void DNServiceRunner::RegisterCommands()
{
	this->Service->Processor->Register(DNCmdType::Echo, new DNCmdEcho(this->Service));
	this->Service->Processor->Register(DNCmdType::ReplyEcho, new DNCmdEchoReply(this->Service));
	this->Service->Processor->Register(DNCmdType::Token, new DNCmdToken(this->Service));
	this->Service->Processor->Register(DNCmdType::ReplyToken, new DNCmdTokenReply(this->Service));
}

void DNServiceRunner::RunServ()
{

	this->Service = new DNServiceManager();

	DNNetworkLayer *networkLayer = new DNNetworkLayer(this->Service);
	DNDataLayer *dataLayer = new DNDataLayer(this->Service);
	DNPacketLayer *packetLayer = new DNPacketLayer(this->Service);
	DNCmdLayer *cmdLayer = new DNCmdLayer(this->Service);
	DNUserLayer *userLayer = new DNUserLayer(this->Service);

	this->Service->NetworkLayer = networkLayer;
	this->Service->DataLayer = dataLayer;
	this->Service->PacketLayer = packetLayer;
	this->Service->CMDLayer = cmdLayer;
	this->Service->UserLayer = userLayer;

	this->Service->Config = this->config;

	this->Service->Processor = new DNCmdProcessor();
	this->RegisterCommands();

	DSocketSystem::Initialize();

	GlobalDF->DebugManager->Log(this, L"Dawn Network Service Initialized");

	this->RunSocket();
}

void DNServiceRunner::StopServ()
{
	this->StopSocket();
	DSocketSystem::Dispose();

	DDel(this->Service->Processor);

	DDel(this->Service->NetworkLayer);
	DDel(this->Service->DataLayer);
	DDel(this->Service->PacketLayer);
	DDel(this->Service->CMDLayer);
	DDel(this->Service->UserLayer);

	GlobalDF->DebugManager->Log(this, L"Dawn Network Service Disposed");
}

void DNServiceRunner::RunSocket()
{
	this->Service->ListenSocket = new DNServerDgramSocket();
	this->Service->ListenSocket->Bind(this->Service->Config->ServiceAddr);
	GlobalDF->DebugManager->Log(this, L"Socket Initialized");
	this->Receiving = true;
	auto RecvFunc = [this]()
	{
		int len;
		DNPacket Packet;
		DSocketAddrIn AddrIn;
		memset(&Packet, 0, sizeof(Packet));

		while (this->Receiving)
		{
			len = this->Service->ListenSocket->Recv(reinterpret_cast<char*>(&Packet), sizeof(Packet), AddrIn);
			if (len > 0)
			{
				DNTransData *TransData = new DNTransData;
				TransData->Addr = std::move(AddrIn);
				TransData->Packet = std::move(Packet);
				this->Service->NetworkLayer->Receive(TransData);
			}
			if (len <= 0)
			{
				Sleep(500);
			}
		}
		this->ThreadDisposed = true;
		return;
	};
	this->ListenThread = new std::thread(RecvFunc);
	GlobalDF->DebugManager->Log(this, L"Socket Receiving");
}

void DNServiceRunner::StopSocket()
{
	GlobalDF->DebugManager->Log(this, L"Socket Disposing");
	this->Receiving = false;
	this->ThreadDisposed = false;
	while (this->ThreadDisposed);
	this->ListenThread->detach();
	DDel(this->Service->ListenSocket);
	DDel(this->ListenThread);
	GlobalDF->DebugManager->Log(this, L"Socket Disposed");
}