#include "stdafx.h"
#include "SerializerFactory.h"
#include "SerializeBinary.h"
#include "SerializeXML.h"
#include "SerializerInterface.h"
#include "QObject.h"


SerializerInterface* SerializerFactory::SerializerInterfaceInstanze = nullptr;

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

SerializerInterface* SerializerFactory::CreateInterface()
{
	//TODO: Will be set by config
	//SerializeGameInterface = new CSaveToXML();
	if( nullptr != SerializerInterfaceInstanze )
	{
		return SerializerInterfaceInstanze;
	}

	SerializerInterfaceInstanze = new SerializerInterface;
	SerializerInterfaceInstanze->SerializeGameInterface = new SerializeXML;
	return SerializerInterfaceInstanze;
}
