#include "stdafx.h"
#include "TerrainTypeRepository.h"
#include "TerrainType.h"

CTerrainTypeRepository::CTerrainTypeRepository()
	: DefaultTerrainType(nullptr)
{
}


CTerrainTypeRepository::~CTerrainTypeRepository()
{
}

bool CTerrainTypeRepository::RegisterTerrainType( CTerrainType *terrainType )
{
	if( terrainType == nullptr )
	{
		Q_ASSERT(false);
		return false;
	}
	QMap<int,CTerrainType*>::const_iterator allreadyExists = TerrainTypes.find(terrainType->GetId() );
	if( allreadyExists != TerrainTypes.end() )
	{
		return false;
	}
	TerrainTypes.insert( terrainType->GetId(), terrainType );
	return true;
}

CTerrainType* CTerrainTypeRepository::FindTerrainTypeById( int id )
{
	QMap<int,CTerrainType*>::iterator exists = TerrainTypes.find( id );
	if( exists == TerrainTypes.end() )
	{
		return nullptr;
	}
	return exists.value();
}

int CTerrainTypeRepository::GetCount() const
{
	return TerrainTypes.size();
}

QMap<int,CTerrainType*>::const_iterator CTerrainTypeRepository::GetFirstIterator() const
{
	return TerrainTypes.cbegin();
}

QMap<int,CTerrainType*>::const_iterator CTerrainTypeRepository::GetLastIterator() const
{
	return TerrainTypes.cend();
}

const CTerrainType* CTerrainTypeRepository::GetDefaultTerrainType() const
{
	return DefaultTerrainType;
}

void CTerrainTypeRepository::SetDefaultTerrainType( const CTerrainType* val )
{
	DefaultTerrainType = val;
}
