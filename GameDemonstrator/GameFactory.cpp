#include "stdafx.h"
#include "GameFactory.h"
#include "GameInitialisationData.h"
#include "model\GameMap.h"
#include "MapView.h"
#include "SaveBinary.h"

//Initialisierung von static membern
GameMap* CGameFactory::TheGameMap = nullptr;

CGameFactory::CGameFactory()
{
}

CGameFactory::~CGameFactory()
{
}

void CGameFactory::CreateNewGame()
{
	TheGameMap = new GameMap;
	TheGameMap->Create();
}

void CGameFactory::CreateNewGame( const CGameInitialisationData& data, CMapView *mapView, const CTerrainType * defaultTerrainType )
{
	CreateModel( data );
	CreateMap( data, mapView, defaultTerrainType );
}

#include "ModelFactory.h"
void CGameFactory::CreateModel( const CGameInitialisationData& data )
{
	CModelFactory modelFactory;

	delete TheGameMap;

	modelFactory.CreateEmptyMap( data, &TheGameMap );
}

void CGameFactory::CreateMap( const CGameInitialisationData& data, CMapView *mapView, const CTerrainType * defaultTerrainType )
{
	mapView->Init( data, defaultTerrainType );
}

