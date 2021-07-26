#include "stdafx.h"
#include "GameFactory.h"
#include "GameInitialisationData.h"
#include "model\GameMap.h"
#include "MapView.h"
#include "SaveBinary.h"

//Initialisierung von static membern
GDModel::GameMap* CGameFactory::TheGameMap = nullptr;

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

	delete TheGameMap;

	modelFactory.CreateEmptyMap( data, &TheGameMap );
	CSaveBinary().SetMap(TheGameMap);
}

void CGameFactory::CreateMap( const GDModel::CGameInitialisationData& data, CMapView *mapView, const CTerrainType * defaultTerrainType )
{
	mapView->Init( data, defaultTerrainType );
}

