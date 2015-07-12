#pragma once
#include "DNLayer.h"

class DNPacketLayer :
	public DNLayer
{
	DClass(DNPacketLayer)
public:
	DNPacketLayer(DNServiceManager *service);
	~DNPacketLayer();

	void Receive(DNTransData *Data);
	void Send(DNTransData *Data);
};
