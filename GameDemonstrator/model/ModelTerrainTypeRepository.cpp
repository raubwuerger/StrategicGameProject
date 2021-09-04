#include "stdafx.h"
#include "ModelTerrainTypeRepository.h"
#include "ModelTerrainType.h"
#include "LogInterface.h"

ModelTerrainTypeRepository* ModelTerrainTypeRepository::Instance = nullptr;

ModelTerrainTypeRepository* ModelTerrainTypeRepository::GetInstance()
{
	if( nullptr != Instance )
	{
		return Instance;
	}

	Instance = new ModelTerrainTypeRepository;
	return Instance;
}

bool ModelTerrainTypeRepository::Init()
{
	TerrainTypes.clear();
	return true;
}

ModelTerrainTypeRepository::ModelTerrainTypeRepository()
	: DefaultTerrainType(nullptr)
{
}

ModelTerrainTypeRepository::~ModelTerrainTypeRepository()
{
	TerrainTypes.clear();
}

bool ModelTerrainTypeRepository::RegisterTerrainType( ModelTerrainType *terrainType )
{
	if( terrainType == nullptr )
	{
		jha::GetLog()->Log_MESSAGE( QObject::tr( "ModelTerrainType must not be null!"));
		return false;
	}
	
	QMap<int,ModelTerrainType*>::const_iterator allreadyExists = TerrainTypes.find(terrainType->GetId() );
	if( allreadyExists != TerrainTypes.end() )
	{
		return false;
	}

	if( true == TerrainTypes.isEmpty() )
	{
		SetDefaultTerrainType( terrainType );
	}

	jha::GetLog()->Log_DEBUG( QObject::tr( "ModelTerrainType registered: ") +terrainType->toString() );

	TerrainTypes.insert( terrainType->GetId(), terrainType );
	return true;
}

ModelTerrainType* ModelTerrainTypeRepository::FindTerrainTypeById( int id )
{
	QMap<int,ModelTerrainType*>::iterator exists = TerrainTypes.find( id );
	if( exists == TerrainTypes.end() )
	{
		return nullptr;
	}
	return exists.value();
}

int ModelTerrainTypeRepository::GetCount() const
{
	return TerrainTypes.size();
}

QMap<int,ModelTerrainType*>::const_iterator ModelTerrainTypeRepository::GetFirstIterator() const
{
	return TerrainTypes.cbegin();
}

QMap<int,ModelTerrainType*>::const_iterator ModelTerrainTypeRepository::GetLastIterator() const
{
	return TerrainTypes.cend();
}

const ModelTerrainType* ModelTerrainTypeRepository::GetDefaultTerrainType() const
{
	return DefaultTerrainType;
}

void ModelTerrainTypeRepository::SetDefaultTerrainType( const ModelTerrainType* val )
{
	DefaultTerrainType = val;
}


void ModelTerrainTypeRepository::Release()
{
	delete Instance;
	Instance = nullptr;
}
