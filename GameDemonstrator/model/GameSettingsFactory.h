#pragma once

class GameSettings;

/** This class holds all game settings */
class GameSettingsFactory
{
public:
	/** */
	GameSettingsFactory();
	/** */
	~GameSettingsFactory();
	/** */
	GameSettings* Create();
private:
	GameSettings* TheGameSettings;
};
