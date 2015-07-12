#include "stdafx.h"
#include "DSocketSystem.h"


DSocketSystem::DSocketSystem()
{
}


DSocketSystem::~DSocketSystem()
{
}

void DSocketSystem::Initialize()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		GlobalDF->DebugManager->ThrowError<DNetworkException>(nullptr, L"WSA Startup Error");
	}
}

void DSocketSystem::Dispose()
{
	WSACleanup();
}

WSADATA DSocketSystem::wsaData;