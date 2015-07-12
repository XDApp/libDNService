#pragma once
#include "DNLayer.h"
class DNCmdLayer :
	public DNLayer
{
	DClass(DNCmdLayer)
public:
	DNCmdLayer(DNServiceManager *service);
	~DNCmdLayer();

	void Receive(DNTransData *Data);
	void Send(DNTransData *Data);
};

