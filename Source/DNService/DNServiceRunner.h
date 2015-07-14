#pragma once

#include <DANetwork/DSocketAddrIn.h>

class DSocketAddrIn;
class DNServerDgramSocket;
class DConfig;
class DNServiceManager;

class DNServiceRunner
	: public DObject
{
	DClass(DNServiceRunner)
public:
	DNServiceManager *Service;
	bool Receiving;
	bool ThreadDisposed;
private:
	std::thread *ListenThread;

	DNConfigManager *config;
public:
	DNServiceRunner(DNConfigManager *Config);
	~DNServiceRunner();

	void RunServ();
	void StopServ();
private:
	void RunSocket();
	void StopSocket();

	void RegisterCommands();
};
