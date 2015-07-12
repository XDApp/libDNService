#pragma once

#include "DNPacket.h"

class DNServiceManager;
class DNLayer
	: public DObject
{
	DClass(DNLayer)
protected:
	DNServiceManager *Service;
public:
	DNLayer(DNServiceManager *service);
	~DNLayer();

	virtual void Receive(DNTransData *Data) = 0;
	virtual void Send(DNTransData *Data) = 0;

	DNTransData* CreatePacket();
	void DestroyPacket(DNTransData *Data);
};

