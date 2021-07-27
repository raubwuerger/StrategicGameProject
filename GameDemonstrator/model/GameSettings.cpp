#include "stdafx.h"
#include "GameSettings.h"

GameSettings::GameSettings()
{
	SaveGamePath = "C:\\";
	DifficultyLevel = "1";
	PlayerCount = "0";
}

GameSettings::~GameSettings()
{
	Players.clear();
}
