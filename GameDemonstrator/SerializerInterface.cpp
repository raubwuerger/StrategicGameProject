#include "stdafx.h"
#include "SerializerInterface.h"

const GDModel::GameMap *CSerializerInterface::TheGameMap = nullptr;

CSerializerInterface::CSerializerInterface()
{
}

CSerializerInterface::~CSerializerInterface()
{
}

void CSerializerInterface::SetMap( const GDModel::GameMap* gameMap )
{
	TheGameMap = gameMap;
}

bool CSerializerInterface::SerializeGame()
{
	return DoSerializeGame( *(this->TheGameMap) );
}

bool CSerializerInterface::DeserializeGame()
{
//	return DoDeserializeMap( *(this->TheGameMap) );
	return false;
}

