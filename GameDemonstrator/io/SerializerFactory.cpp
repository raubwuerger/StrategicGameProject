#include "stdafx.h"
#include "SerializerFactory.h"
#include "SerializeBinary.h"
#include "SerializeXML.h"
#include "SerializerGame.h"
#include "QObject.h"


SerializerGame* SerializerFactory::SerializerInterfaceInstanze = nullptr;

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

SerializerGame* SerializerFactory::CreateInterface()
{
	//TODO: Will be set by config
	//SerializeGameInterface = new CSaveToXML();
	if( nullptr != SerializerInterfaceInstanze )
	{
		return SerializerInterfaceInstanze;
	}

	SerializerInterfaceInstanze = new SerializerGame;
	SerializerInterfaceInstanze->SerializeGameInterface = new SerializeXML;
	return SerializerInterfaceInstanze;
}
