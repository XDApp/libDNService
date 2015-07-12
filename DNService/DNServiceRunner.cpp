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

DNServiceRunner::DNServiceRunner()
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

	DNNetworkLayer *networkLayer = new DNNetworkLayer(DNServiceRunner::Service);
	DNDataLayer *dataLayer = new DNDataLayer(DNServiceRunner::Service);
	DNPacketLayer *packetLayer = new DNPacketLayer(DNServiceRunner::Service);
	DNCmdLayer *cmdLayer = new DNCmdLayer(DNServiceRunner::Service);
	DNUserLayer *userLayer = new DNUserLayer(DNServiceRunner::Service);

	this->Service->NetworkLayer = networkLayer;
	this->Service->DataLayer = dataLayer;
	this->Service->PacketLayer = packetLayer;
	this->Service->CMDLayer = cmdLayer;
	this->Service->UserLayer = userLayer;

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

	GlobalDF->DebugManager->Log(this, L"[Log] Dawn Network Service Disposed");
}

void DNServiceRunner::RunSocket()
{
	this->Service->ListenSocket = new DNServerDgramSocket();
	this->ListenAddr = DSocketAddrIn(6000);
	this->Service->ListenSocket->Bind(this->ListenAddr);
	GlobalDF->DebugManager->Log(this, L"[Log] Socket Initialized");
	this->Receiving = true;
	auto RecvFunc = [this]()
	{
		int len;
		DNPacket Packet;
		DSocketAddrIn AddrIn;
		memset(&Packet, 0, sizeof(Packet));

		while (this->Receiving)
		{
			//while (!this->Service->SocketLock.try_lock())Sleep(10);
			len = this->Service->ListenSocket->Recv((char*)&Packet, sizeof(Packet), AddrIn);
			//this->Service->SocketLock.unlock();
			if (len > 0)
			{
				DNTransData *TransData = new DNTransData;
				TransData->Addr = AddrIn;
				TransData->Packet = Packet;
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
	GlobalDF->DebugManager->Log(this, L"[Log] Socket Receiving");
}

void DNServiceRunner::StopSocket()
{
	GlobalDF->DebugManager->Log(this, L"[Log] Socket Disposing");
	this->Receiving = false;
	this->ThreadDisposed = false;
	while (this->ThreadDisposed);
	this->ListenThread->detach();
	DDel(this->Service->ListenSocket);
	DDel(this->ListenThread);
	GlobalDF->DebugManager->Log(this, L"[Log] Socket Disposed");
}