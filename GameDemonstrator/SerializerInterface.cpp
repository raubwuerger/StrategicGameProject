#include "stdafx.h"
#include "SerializerInterface.h"

const GDModel::CMap *CSerializerInterface::Map = nullptr;

CSerializerInterface::CSerializerInterface()
{
}

CSerializerInterface::~CSerializerInterface()
{
}

void CSerializerInterface::SetMap( const GDModel::CMap* map )
{
	Map = map;
}

bool CSerializerInterface::SerializeGame()
{
	return DoSerializeGame( *(this->Map) );
}

bool CSerializerInterface::DeserializeGame()
{
//	return DoDeserializeMap( *(this->Map) );
	return false;
}

