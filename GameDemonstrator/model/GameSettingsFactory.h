#pragma once

/** This class holds all game settings */

/** Repräsentiert die Karte im Speicher */
class GameSettingsFactory
{
public:
	/** */
	GameSettingsFactory();
	/** */
	~GameSettingsFactory();
	/** */
	void Create();
	/** */
	void Release();
};
