#include "stdafx.h"
#include "DNLayer.h"
#include "DNServiceManager.h"

DNLayer::DNLayer(DNServiceManager* service) :Service(service)
{
}


DNLayer::~DNLayer()
{
}

DNTransData* DNLayer::CreatePacket()
{
	DNTransData *Data = new DNTransData;
	return Data;
}

void DNLayer::DestroyPacket(DNTransData *Data)
{
	DDel(Data);
}