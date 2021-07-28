#include "stdafx.h"
#include "ModelSettings.h"

ModelSettings::ModelSettings()
{
	SaveGamePath = "C:\\";
	DifficultyLevel = "1";
	PlayerCount = "0";
}

ModelSettings::~ModelSettings()
{
	Players.clear();
}
