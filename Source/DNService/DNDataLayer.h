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

	void __RSAEncryptData(DNTransData *Data, EVP_PKEY* RSAKey);
	void __RSADecryptData(DNTransData *Data, EVP_PKEY* RSAKey);
};

