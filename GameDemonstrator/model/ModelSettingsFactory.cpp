#include "stdafx.h"
#include "ModelSettingsFactory.h"
#include "ModelSettings.h"

ModelSettingsFactory* ModelSettingsFactory::Instance = nullptr;

ModelSettingsFactory* ModelSettingsFactory::GetInstance()
{
	if( nullptr != Instance )
	{
		return Instance;
	}

	Instance = new ModelSettingsFactory;
	return Instance;
}

void ModelSettingsFactory::Release()
{
	delete Instance;
	Instance = nullptr;
}

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
	TheGameSettings->CurrentSaveGameFileName = "PlayerName_1900_01.xml"; //TODO: Muss aus Dialog entnommen werden!
	return TheGameSettings;
}

