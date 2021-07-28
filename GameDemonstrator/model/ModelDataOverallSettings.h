#pragma once

/** This class holds all game configs (Map, Settings, Player, ...) */

#include "GameMapConfig.h"

/** Repr�sentiert alle Einstellungen des Spiels */
class ModelDataOverallSettings
{
public:
	static ModelDataOverallSettings* GetInstance();
/** */
	GameMapConfig* GetGameMapConfig();
private:
	/** */
	ModelDataOverallSettings() {}
private:
	static ModelDataOverallSettings* Instance;
};
