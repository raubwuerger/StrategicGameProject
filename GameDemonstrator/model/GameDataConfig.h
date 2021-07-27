#pragma once

/** This class holds all game configs (Map, Settings, Player, ...) */

#include "GameMapConfig.h"

/** Repr�sentiert alle Einstellungen des Spiels */
class GameDataConfig
{
public:
	static GameDataConfig* GetInstance();
/** */
	GameMapConfig* GetGameMapConfig();
private:
	/** */
	GameDataConfig() {}
private:
	static GameDataConfig* Instance;
};
