#include "stdafx.h"
#include "GameFactory.h"
#include "GameInitialisationData.h"
#include "model\GameMap.h"
#include "MapView.h"
#include "SaveBinary.h"
#include "MapFactory.h"
#include "ModelFactory.h"

//Initialisierung von static membern
GameMap* GameFactory::TheGameMap = nullptr;

GameFactory* GameFactory::Instance = nullptr;

GameFactory* GameFactory::GetInstance()
{
	if( nullptr != Instance )
	{
		return Instance;
	}

	Instance = new GameFactory();
	return Instance;
}

GameFactory::GameFactory()
{
}

GameFactory::~GameFactory()
{
}

void GameFactory::CreateNewGame()
{
	if( nullptr == MapViewInstance )
	{
		Q_ASSERT(MapViewInstance);
		return;
	}

	ModelFactory modelFactory;
	modelFactory.CreateEmptyMap( &TheGameMap );

	TheGameMap = new GameMap;
	TheGameMap->Create();

	MapFactory::GetInstance()->CreateNewMapFunction();

/*	CreateNewMap *newMapCreator = new CreateNewMap(parent);
	newMapCreator->MapView = mapView;
	newMapCreator->DefaultTerrainType = defaultTerrainType;
	QObject::connect(action, SIGNAL(triggered()), newMapCreator, SLOT(DoCreateNewMap()), Qt::QueuedConnection );
*/
	MapViewInstance->Create();
}

void GameFactory::CreateNewGame( const GameInitialisationData& data, MapView *mapView, const TerrainType * defaultTerrainType )
{
	CreateModel( data );
	CreateMap( data, mapView, defaultTerrainType );
}

#include "ModelFactory.h"
void GameFactory::CreateModel( const GameInitialisationData& data )
{
	ModelFactory modelFactory;

	delete TheGameMap;

	modelFactory.CreateEmptyMap( data, &TheGameMap );
}

void GameFactory::CreateMap( const GameInitialisationData& data, MapView *mapView, const TerrainType * defaultTerrainType )
{
	mapView->Init( data, defaultTerrainType );
}

