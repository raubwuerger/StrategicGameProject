#include "stdafx.h"
#include "ModelSettingsFactory.h"
#include "ModelSettings.h"

ModelSettingsFactory::ModelSettingsFactory()
{
	TheGameSettings = new ModelSettings();
}

ModelSettingsFactory::~ModelSettingsFactory()
{
	delete TheGameSettings;
}

ModelSettings* ModelSettingsFactory::Create()
{
	//TODO: Should be read from dialogs
	TheGameSettings->SaveGamePath = "";
	TheGameSettings->DifficultyLevel = "1";
	TheGameSettings->Players.push_back( "Player 1" );
	TheGameSettings->Players.push_back( "Player 2" );
	TheGameSettings->PlayerCount = TheGameSettings->Players.count();
	return TheGameSettings;
}

