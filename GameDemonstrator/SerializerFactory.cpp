#include "stdafx.h"
#include "SerializerFactory.h"
#include "SaveBinary.h"
#include "SaveToXML.h"
#include "SerializerInterface.h"
#include "QObject.h"


CSerializerInterface* CSerializerFactory::SerializerInterface = nullptr;

CSerializerFactory::CSerializerFactory()
{
}

CSerializerFactory::~CSerializerFactory()
{
}

void CSerializerFactory::Release()
{
	delete SerializerInterface;
	SerializerInterface = nullptr;
}

CSerializerInterface* CSerializerFactory::CreateInterface()
{
	//TODO: Will be set by config
	//SerializeGameInterface = new CSaveToXML();
	SerializerInterface = new CSerializerInterface;
	SerializerInterface->SerializeGameInterface = new CSaveToXML;
	return SerializerInterface;
}
