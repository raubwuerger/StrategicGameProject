#include "stdafx.h"
#include "SerializerGame.h"
#include "SerializeXML.h"
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

bool SerializerGame::LoadGame()
{
	if( nullptr == SerializeGameInterface )
	{
		Q_ASSERT( SerializeGameInterface != nullptr );
		return false;
	}
	return SerializeGameInterface->LoadGame( GameConfig::CurrentSaveGameName );
}
