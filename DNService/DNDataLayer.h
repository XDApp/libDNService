#pragma once
#include "DNLayer.h"

class DNDataLayer :
	public DNLayer
{
	DClass(DNDataLayer)
public:
	DNDataLayer(DNServiceManager *service);
	~DNDataLayer();

	void Receive(DNTransData *Data);
	void Send(DNTransData *Data);

	void EncryptData(DNTransData *Data);
	void DecryptData(DNTransData *Data);
};

