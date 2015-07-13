#include "stdafx.h"
#include "DAConfigManager.h"


DAConfigManager::DAConfigManager()
	: DNConfigManager(),
	DCoreConfigManager()
{
}


DAConfigManager::~DAConfigManager()
{
}

void DAConfigManager::Load()
{
	DCoreConfigManager::Load();
	DNConfigManager::Load();
}

void DAConfigManager::Save()
{
	DCoreConfigManager::Save();
	DNConfigManager::Save();
}