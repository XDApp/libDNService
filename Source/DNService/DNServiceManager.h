#pragma once

class DSocket;
class DNLayer;
class DNCmdProcessor;
class DNConfigManager;

class DNServiceManager
	: public DObject
{
	DClass(DNServiceManager)
public:
	DNServiceManager();
	~DNServiceManager();
	DNLayer *NetworkLayer;
	DNLayer *PacketLayer;
	DNLayer *DataLayer;
	DNLayer *CMDLayer;
	DNLayer *UserLayer;

	DSocket *ListenSocket;
	std::mutex SocketLock;

	DNCmdProcessor *Processor;

	DNConfigManager* Config;
};

