#include "stdafx.h"
#include "TerrainTypeRepository.h"
#include "TerrainType.h"

CTerrainTypeRepository::CTerrainTypeRepository()
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
	QMap<int,CTerrainType*>::const_iterator allreadyExists = m_TerrainTypes.find(terrainType->GetId() );
	if( allreadyExists != m_TerrainTypes.end() )
	{
		return false;
	}
	m_TerrainTypes.insert( terrainType->GetId(), terrainType );
	return true;
}

CTerrainType* CTerrainTypeRepository::FindTerrainTypeById( int id )
{
	QMap<int,CTerrainType*>::iterator exists = m_TerrainTypes.find( id );
	if( exists != m_TerrainTypes.end() )
	{
		return nullptr;
	}
	return exists.value();
}

int CTerrainTypeRepository::GetCount() const
{
	return m_TerrainTypes.size();
}

QMap<int,CTerrainType*>::const_iterator CTerrainTypeRepository::GetFirstIterator()
{
	return m_TerrainTypes.cbegin();
}
