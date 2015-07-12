#pragma once
#include "DNLayer.h"

class DNNetworkLayer :
	public DNLayer
{
	DClass(DNNetworkLayer)
public:
	DNNetworkLayer(DNServiceManager *service);
	~DNNetworkLayer();

	void Receive(DNTransData *Data);
	void Send(DNTransData *Data);
};

