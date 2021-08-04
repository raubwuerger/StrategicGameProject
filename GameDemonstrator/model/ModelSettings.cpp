#include "stdafx.h"
#include "ModelSettings.h"

ModelSettings::ModelSettings()
	: ModelSettingsFileName(".\\conf\\GameDemonstrator.xml"),
		RootName("GameDemonstrator")
{
	SaveGamePath = "C:\\";
	DifficultyLevel = "1";
	PlayerCount = "0";
}

ModelSettings::~ModelSettings()
{
	Players.clear();
}
