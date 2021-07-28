#pragma once

class ModelSettings;

/** This class holds all game settings */
class ModelSettingsFactory
{
public:
	/** */
	ModelSettingsFactory();
	/** */
	~ModelSettingsFactory();
	/** */
	ModelSettings* Create();
private:
	ModelSettings* TheGameSettings;
};
