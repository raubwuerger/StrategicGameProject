#include "stdafx.h"
#include "GameFactory.h"
#include "GameInitialisationData.h"
#include "model\Map.h"
#include "MapView.h"
#include "SaveBinary.h"

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

	modelFactory.CreateEmptyMap( data, &Map );
	CSaveBinary().SetMap(Map);
}

void CGameFactory::CreateMap( const GDModel::CGameInitialisationData& data, CMapView *mapView, const CTerrainType * defaultTerrainType )
{
	mapView->Init( data, defaultTerrainType );
}

