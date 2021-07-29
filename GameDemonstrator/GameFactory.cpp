#include "stdafx.h"
#include "GameFactory.h"
#include "model\GameMap.h"
#include "MapView.h"
#include "MapFactory.h"
#include "ModelFactory.h"
#include "model\ModelMapConfigFactory.h"

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

void GameFactory::Release()
{
	delete Instance;
}

GameFactory::GameFactory()
	: TheGameMap(nullptr)
{
}

GameFactory::~GameFactory()
{
	delete TheGameMap;
}

void GameFactory::CreateNewGame()
{
	if( nullptr == MapViewInstance )
	{
		Q_ASSERT(MapViewInstance);
		return;
	}

	ModelMapConfigFactory::GetInstance()->CreateMap();

//	ModelFactory modelFactory;
//	modelFactory.CreateEmptyMap( &TheGameMap );

	TheGameMap = new ModelMapRepository;
	TheGameMap->Create();

	MapFactory::GetInstance()->CreateNewMapFunction();
	MapViewInstance->Create();
}

void GameFactory::SetMapView( MapView* mapView )
{
	MapViewInstance = mapView;
}

