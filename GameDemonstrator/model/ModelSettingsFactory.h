#pragma once

class ModelSettings;

/** This class holds all game settings */
class ModelSettingsFactory
{
public:
	/** */
	static ModelSettingsFactory* GetInstance();
	/** */
	void Release();
	/** */
	ModelSettings* Create();
private:
	/** */
	ModelSettingsFactory();
	/** */
	~ModelSettingsFactory();
private:
	ModelSettings* TheGameSettings;
	static ModelSettingsFactory* Instance;
};
