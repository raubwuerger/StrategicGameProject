#include "stdafx.h"
#include "SerializerFactory.h"
#include "SaveBinary.h"
#include "SerializerInterface.h"

CSerializerInterface* CSerializerFactory::Interfaces = nullptr;

CSerializerFactory::CSerializerFactory()
{
}

CSerializerFactory::~CSerializerFactory()
{
}

void CSerializerFactory::Release()
{
	delete Interfaces;
}

CSerializerInterface* CSerializerFactory::CreateInterface( QAction *action )
{
	Interfaces = new CSaveBinary(action);
	return Interfaces;
}
