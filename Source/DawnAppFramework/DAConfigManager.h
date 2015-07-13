#pragma once

class DAConfigManager
	: public DNConfigManager,
	public DCoreConfigManager
{
	DClass(DAConfigManager)
public:
	DAConfigManager();
	~DAConfigManager();

	void Load() final;
	void Save() final;
};

