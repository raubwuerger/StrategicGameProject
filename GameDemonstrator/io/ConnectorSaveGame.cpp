#include "stdafx.h"
#include "ConnectorSaveGame.h"
#include "SerializeXML.h"
#include "game\GameMainCounter.h"
#include "GameConfig.h"
#include "model\ModelProgramFactory.h"
#include "model\ModelProgramSettings.h"

ConnectorSaveGame::ConnectorSaveGame()
	: SerializeGameInterface(nullptr)
{
}

ConnectorSaveGame::~ConnectorSaveGame()
{
	delete SerializeGameInterface;
}

bool ConnectorSaveGame::SaveGame()
{
	if( nullptr == SerializeGameInterface )
	{
		Q_ASSERT( SerializeGameInterface != nullptr );
		return false;
	}
	return SerializeGameInterface->SaveGame( CreateSaveGameFileName() );
}

bool ConnectorSaveGame::LoadGame()
{
	if( nullptr == SerializeGameInterface )
	{
		Q_ASSERT( SerializeGameInterface != nullptr );
		return false;
	}
	return SerializeGameInterface->LoadGame( GameConfig::CurrentSaveGameName );
}

QString ConnectorSaveGame::CreateSaveGameFileName() const
{
	QString saveGamePath(ModelProgramFactory::ModelProgramSettingsInstance->SaveGamePath);
	QString saveGameFile(saveGamePath);
	saveGameFile += "PlayerName_";
	saveGameFile += GameMainCounter::GetInstance()->GetCurrentDate().toString( "yyyy_MM" );
	saveGameFile += ".xml";

	QDir().mkpath(saveGamePath);
	return saveGameFile;
}


