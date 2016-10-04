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

bool CSerializerInterface::SerializeMap()
{
	return DoSerializeMap( *(this->Map) );
}

bool CSerializerInterface::DeserializeMap()
{
//	return DoDeserializeMap( *(this->Map) );
	return false;
}

