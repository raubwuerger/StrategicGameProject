#include "stdafx.h"
#include "GameSettingsFactory.h"
#include "GameSettings.h"

GameSettingsFactory::GameSettingsFactory()
{
	TheGameSettings = new GameSettings();
}

GameSettingsFactory::~GameSettingsFactory()
{
	delete TheGameSettings;
}

GameSettings* GameSettingsFactory::Create()
{
	//TODO: Should be read from dialogs
	TheGameSettings->SaveGamePath = "";
	TheGameSettings->DifficultyLevel = "1";
	TheGameSettings->Players.push_back( "Player 1" );
	TheGameSettings->Players.push_back( "Player 2" );
	TheGameSettings->PlayerCount = TheGameSettings->Players.count();
	return TheGameSettings;
}

