#pragma once

/** This class holds all game configs (Map, Settings, Player, ...) */

#include "GameMapConfig.h"

/** Repr�sentiert die Karte im Speicher */
class GameDataConfig
{
public:
	static GameDataConfig* GetInstance();
public:
	GameMapConfig TheGameMapConfig;
private:
	/** */
	GameDataConfig() {}
private:
	static GameDataConfig* Instance;
};
