#include "stdafx.h"
#include "SerializerFactory.h"
#include "SerializeBinary.h"
#include "SerializeXML.h"
#include "ConnectorSaveGame.h"
#include "QObject.h"


ConnectorSaveGame* SerializerFactory::SerializerInterfaceInstanze = nullptr;

SerializerFactory::SerializerFactory()
{
}

SerializerFactory::~SerializerFactory()
{
}

void SerializerFactory::Release()
{
	delete SerializerInterfaceInstanze;
	SerializerInterfaceInstanze = nullptr;
}

ConnectorSaveGame* SerializerFactory::CreateInterface()
{
	//TODO: Will be set by config
	//SerializeGameInterface = new CSaveToXML();
	if( nullptr != SerializerInterfaceInstanze )
	{
		return SerializerInterfaceInstanze;
	}

	SerializerInterfaceInstanze = new ConnectorSaveGame;
	SerializerInterfaceInstanze->SerializeGameInterface = new SerializeXML;
	return SerializerInterfaceInstanze;
}
