#include "stdafx.h"
#include "TerrainTypeRepository.h"
#include "TerrainType.h"

TerrainTypeRepository* TerrainTypeRepository::Instance = nullptr;

TerrainTypeRepository* TerrainTypeRepository::GetInstance()
{
	if( nullptr != Instance )
	{
		return Instance;
	}

	Instance = new TerrainTypeRepository;
	return Instance;
}

TerrainTypeRepository::TerrainTypeRepository()
	: DefaultTerrainType(nullptr)
{
}

TerrainTypeRepository::~TerrainTypeRepository()
{
	TerrainTypes.clear();
}

bool TerrainTypeRepository::RegisterTerrainType( TerrainType *terrainType )
{
	if( terrainType == nullptr )
	{
		Q_ASSERT(false);
		return false;
	}
	
	QMap<int,TerrainType*>::const_iterator allreadyExists = TerrainTypes.find(terrainType->GetId() );
	if( allreadyExists != TerrainTypes.end() )
	{
		return false;
	}

	if( true == TerrainTypes.isEmpty() )
	{
		SetDefaultTerrainType( terrainType );
	}

	TerrainTypes.insert( terrainType->GetId(), terrainType );
	return true;
}

TerrainType* TerrainTypeRepository::FindTerrainTypeById( int id )
{
	QMap<int,TerrainType*>::iterator exists = TerrainTypes.find( id );
	if( exists == TerrainTypes.end() )
	{
		return nullptr;
	}
	return exists.value();
}

int TerrainTypeRepository::GetCount() const
{
	return TerrainTypes.size();
}

QMap<int,TerrainType*>::const_iterator TerrainTypeRepository::GetFirstIterator() const
{
	return TerrainTypes.cbegin();
}

QMap<int,TerrainType*>::const_iterator TerrainTypeRepository::GetLastIterator() const
{
	return TerrainTypes.cend();
}

const TerrainType* TerrainTypeRepository::GetDefaultTerrainType() const
{
	return DefaultTerrainType;
}

void TerrainTypeRepository::SetDefaultTerrainType( const TerrainType* val )
{
	DefaultTerrainType = val;
}


void TerrainTypeRepository::Release()
{
	delete Instance;
	Instance = nullptr;
}
