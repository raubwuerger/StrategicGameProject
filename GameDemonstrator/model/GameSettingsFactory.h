#pragma once

class ModelSettings;

/** This class holds all game settings */
class GameSettingsFactory
{
public:
	/** */
	GameSettingsFactory();
	/** */
	~GameSettingsFactory();
	/** */
	ModelSettings* Create();
private:
	ModelSettings* TheGameSettings;
};
