#include "stdafx.h"
#include "SerializerFactory.h"
#include "SaveBinary.h"
#include "SaveToXML.h"
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
	SerializerInterfaceInstanze = new SerializerInterface;
	SerializerInterfaceInstanze->SerializeGameInterface = new SaveToXML;
	return SerializerInterfaceInstanze;
}
