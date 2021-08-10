#include "stdafx.h"
#include "SerializerGame.h"
#include "SerializeXML.h"
#include "game\GameMainCounter.h"
#include "game\GameConfig.h"
#include "model\ModelProgramFactory.h"
#include "model\ModelProgramSettings.h"

SerializerGame::SerializerGame()
	: SerializeGameInterface(nullptr)
{
}

SerializerGame::~SerializerGame()
{
	delete SerializeGameInterface;
}

bool SerializerGame::SlotSaveGame()
{
	if( nullptr == SerializeGameInterface )
	{
		Q_ASSERT( SerializeGameInterface != nullptr );
		return false;
	}
	return SerializeGameInterface->SaveGame( CreateSaveGameFileName() );
}

bool SerializerGame::LoadGame()
{
	if( nullptr == SerializeGameInterface )
	{
		Q_ASSERT( SerializeGameInterface != nullptr );
		return false;
	}
	return SerializeGameInterface->LoadGame( GameConfig::CurrentSaveGameName );
}

QString SerializerGame::CreateSaveGameFileName() const
{
	QString saveGamePath(ModelProgramFactory::ModelProgramSettingsInstance->SaveGamePath);
	QString saveGameFile(saveGamePath);
	saveGameFile += "PlayerName_";
	saveGameFile += GameMainCounter::GetInstance()->GetCurrentDate().toString( "yyyy_MM" );
	saveGameFile += ".xml";

	QDir().mkpath(saveGamePath);
	return saveGameFile;
}


