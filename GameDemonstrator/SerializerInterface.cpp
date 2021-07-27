#include "stdafx.h"
#include "SerializerInterface.h"
#include "SaveToXML.h"

CSerializerInterface::CSerializerInterface()
	: SerializeGameInterface(nullptr)
{
}

CSerializerInterface::~CSerializerInterface()
{
	delete SerializeGameInterface;
}

bool CSerializerInterface::SaveGame()
{
	if( nullptr == SerializeGameInterface )
	{
		Q_ASSERT( SerializeGameInterface != nullptr );
		return false;
	}
	return SerializeGameInterface->SaveGame();
}

bool CSerializerInterface::LoadGame()
{
	if( nullptr == SerializeGameInterface )
	{
		Q_ASSERT( SerializeGameInterface != nullptr );
		return false;
	}
	return SerializeGameInterface->LoadGame();
}

