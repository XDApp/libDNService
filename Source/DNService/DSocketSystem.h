#pragma once
class DSocketSystem
{
	DClass(DSocketSystem)
public:
	DSocketSystem();
	virtual ~DSocketSystem();

	static WSADATA wsaData;
	static void Initialize();
	static void Dispose();
};

