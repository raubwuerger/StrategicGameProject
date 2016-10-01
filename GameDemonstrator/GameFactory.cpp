#include "stdafx.h"
#include "GameFactory.h"
#include "GameInitialisationData.h"
#include "model\Map.h"
#include "MapView.h"

//Initialisierung von static membern
GDModel::CMap* CGameFactory::Map = nullptr;

CGameFactory::CGameFactory()
{
}

CGameFactory::~CGameFactory()
{
}

void CGameFactory::CreateNewGame( const GDModel::CGameInitialisationData& data, CMapView *mapView, const CTerrainType * defaultTerrainType )
{
	CreateModel( data );
	CreateMap( data, mapView, defaultTerrainType );
}

#include "ModelFactory.h"
void CGameFactory::CreateModel( const GDModel::CGameInitialisationData& data )
{
	GDModel::CModelFactory modelFactory;

	delete Map;
	Map = new GDModel::CMap;

	modelFactory.CreateEmptyMap( data, Map );
}

void CGameFactory::CreateMap( const GDModel::CGameInitialisationData& data, CMapView *mapView, const CTerrainType * defaultTerrainType )
{
	mapView->Init( data, defaultTerrainType );
}

