#include "stdafx.h"
#include "SerializerInterface.h"
#include "SerializeXML.h"
#include "game\GameMainCounter.h"
#include "model\ModelSettingsFactory.h"
#include "model\ModelSettings.h"

SerializerInterface::SerializerInterface()
	: SerializeGameInterface(nullptr)
{
}

SerializerInterface::~SerializerInterface()
{
	delete SerializeGameInterface;
}

bool SerializerInterface::SaveGame()
{
	if( nullptr == SerializeGameInterface )
	{
		Q_ASSERT( SerializeGameInterface != nullptr );
		return false;
	}
	return SerializeGameInterface->SaveGame( CreateSaveGameFileName() );
}

bool SerializerInterface::LoadGame()
{
	if( nullptr == SerializeGameInterface )
	{
		Q_ASSERT( SerializeGameInterface != nullptr );
		return false;
	}
	return SerializeGameInterface->LoadGame( ModelSettingsFactory::GetInstance()->Create()->CurrentSaveGameFileName );
}

QString SerializerInterface::CreateSaveGameFileName() const
{
	QString saveGamePath(".\\savegames\\");
	QString saveGameFile(saveGamePath);
	saveGameFile += "PlayerName_";
	saveGameFile += GameMainCounter::GetInstance()->GetCurrentDate().toString( "yyyy_MM" );
	saveGameFile += ".xml";

	QDir().mkpath(".\\savegames\\");
	return saveGameFile;
}


