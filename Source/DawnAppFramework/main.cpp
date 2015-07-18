#include "stdafx.h"
#include "DAConfigManager.h"

DReference *GlobalDF;

class DApp
{
private:
	DEngineManager *Engine;
	DNServiceRunner *Manager;

public:
	DApp()
		: Engine(new DEngineManager())
	{
		DCryptRSA::Initialize();

		GlobalDF = Engine->DF;
		this->Engine->BeforeInitialize->AddHandler(new DEventHandler([this](DObject* Sender)
		{
			DAConfigManager *Config = new DAConfigManager();
			Sender->DF->ConfigManager = Config;
			Sender->DF->DebugManager = new DDebugManager();

			this->Manager = new DNServiceRunner(Config);

			DRSAKey *Key = new DRSAKey(2048);
			Config->LocalPriKey = DCryptRSA::ToEVP(Key->GetPriKey());
			Config->LocalPubKey = DCryptRSA::ToEVP(Key->GetPubKey());
			Config->ServiceAddr = DSocketAddrIn(8000);
			Config->Key_Bits = 2048;
		}));
		this->Engine->AfterDispose->AddHandler(new DEventHandler([this](DObject* Sender)
		{
			DAConfigManager *Config = Sender->DF->ConfigManager->GetConfig<DAConfigManager>();

			DDel(Config->LocalPubKey);
			DDel(Config->LocalPriKey);
			DDel(Sender->DF->DebugManager);
			DDel(Sender->DF->ConfigManager);
		}));
	};

	void Initialize()
	{
		this->Engine->Initialize();
	}
	void Dispose()
	{
		this->Engine->Dispose();
	}

	~DApp() 
	{
		DDel(this->Manager);
		DDel(this->Engine);

		DCryptRSA::Dispose();
	};

	void Loop()
	{
		Manager->RunServ();

		DNUserLayer *userLayer = dynamic_cast<DNUserLayer*>(Manager->Service->UserLayer);

		DNCmdTokenReply* RTokenCmd = this->Manager->Service->Processor->ParseCmd<DNCmdTokenReply>(DNCmdType::ReplyToken);
		DNCmdToken* TokenCmd = this->Manager->Service->Processor->ParseCmd<DNCmdToken>(DNCmdType::Token);
		DNCmdConnect* ConnectCmd = this->Manager->Service->Processor->ParseCmd<DNCmdConnect>(DNCmdType::Connect);

		RTokenCmd->WhenRecv->AddHandler(new DEventHandler([](DObject *Sender){
			auto Data = dynamic_cast<DNTransData*>(Sender);
			char tmp[1500];
			strncpy_s(tmp, Data->Data, Data->Size);
			if (Data) GlobalDF->DebugManager->Log(nullptr, (L"Token Recved: " + DUtil::ANSIToUnicode(tmp)).c_str());
		}));
		
		
		//ConnectCmd->Send(DSocketAddrIn("192.168.0.105", 8000));
		while (true)
		{
			TokenCmd->Send(DSocketAddrIn("192.168.0.105", 8000));
			Sleep(500);
		}
		Manager->StopServ();

		this->Engine->Update();
		this->Engine->Render();
	}
};

void test_Hash()
{
	DNKHash _hash("aaaaaaaaaaaaaaaaaaaa");
	DNKHash hash(std::move(_hash));
	for (int i = 0; i < DNKHash_Size; i++)
	{
		std::cout << hash[i];
	}
	std::cout << std::endl;
	return;
}

int _tmain(int argc, _TCHAR* argv[])
{
	//DApp *App = new DApp();
	//App->Initialize();
	//App->Loop();
	//App->Dispose();
	//test_Crypt();
	//DDel(App);
	test_Hash();
	system("pause");
	return 0;
}

