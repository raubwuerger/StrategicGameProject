#include "stdafx.h"
#include "GameSettingsFactory.h"
#include "ModelSettings.h"

GameSettingsFactory::GameSettingsFactory()
{
	TheGameSettings = new ModelSettings();
}

GameSettingsFactory::~GameSettingsFactory()
{
	delete TheGameSettings;
}

ModelSettings* GameSettingsFactory::Create()
{
	//TODO: Should be read from dialogs
	TheGameSettings->SaveGamePath = "";
	TheGameSettings->DifficultyLevel = "1";
	TheGameSettings->Players.push_back( "Player 1" );
	TheGameSettings->Players.push_back( "Player 2" );
	TheGameSettings->PlayerCount = TheGameSettings->Players.count();
	return TheGameSettings;
}

