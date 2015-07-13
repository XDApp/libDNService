#include "stdafx.h"
#include "DNCmdConnect.h"


DNCmdConnect::DNCmdConnect(DNServiceManager* service) :DNCmd(service)
{
}


DNCmdConnect::~DNCmdConnect()
{
}

DNCmdConnectReply::DNCmdConnectReply(DNServiceManager* service) :DNCmd(service)
{
}


DNCmdConnectReply::~DNCmdConnectReply()
{
}
