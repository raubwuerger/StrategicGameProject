#include "stdafx.h"
#include "SerializerInterface.h"
#include "SerializeXML.h"

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
	return SerializeGameInterface->SaveGame();
}

bool SerializerInterface::LoadGame()
{
	if( nullptr == SerializeGameInterface )
	{
		Q_ASSERT( SerializeGameInterface != nullptr );
		return false;
	}
	return SerializeGameInterface->LoadGame();
}

