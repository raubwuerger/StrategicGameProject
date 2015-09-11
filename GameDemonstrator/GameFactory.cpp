#include "stdafx.h"
#include "GameFactory.h"
#include "GameInitialisationData.h"
#include "model\Map.h"
#include "MapView.h"

CGameFactory::CGameFactory()
{
}

CGameFactory::~CGameFactory()
{
}

void CGameFactory::CreateNewGame( const GDModel::CGameInitialisationData& data, MapView *mapView, const CTerrainType * defaultTerrainType )
{
	CreateModel( data );
	CreateMap( data, mapView, defaultTerrainType );
}

#include "ModelFactory.h"
void CGameFactory::CreateModel( const GDModel::CGameInitialisationData& data )
{
	GDModel::CModelFactory modelFactory;

	GDModel::CMap map;
	modelFactory.CreateEmptyMap( data, &map );
}

void CGameFactory::CreateMap( const GDModel::CGameInitialisationData& data, MapView *mapView, const CTerrainType * defaultTerrainType )
{
	mapView->Init( data, defaultTerrainType );
}

