#pragma once

/** This class holds all game configs (Map, Settings, Player, ...) */

#include "ModelMapConfig.h"

/** Repr�sentiert alle Einstellungen des Spiels */
class ModelDataOverallSettings
{
public:
	static ModelDataOverallSettings* GetInstance();
/** */
	ModelMapConfig* GetGameMapConfig();
private:
	/** */
	ModelDataOverallSettings() {}
private:
	static ModelDataOverallSettings* Instance;
};
