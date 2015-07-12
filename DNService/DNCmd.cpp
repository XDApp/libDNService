#include "stdafx.h"
#include "DNCmd.h"
#include "DNLayer.h"
#include "DNUserLayer.h"
#include "DNServiceManager.h"

DNCmd::DNCmd(DNServiceManager* service) :Service(service)
{
}


DNCmd::~DNCmd()
{
}

void DNCmd::Send(const DSocketAddrIn &Addr)
{

}

void DNCmd::Recv(DNTransData* Data)
{

}

DNTransData* DNCmd::CreatePacket()
{
	DNTransData *Data = new DNTransData;
	return Data;
}

void DNCmd::DestroyPacket(DNTransData *Data)
{
	
	Data;
}