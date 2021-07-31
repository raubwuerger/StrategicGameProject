#include "stdafx.h"
#include "GameFactory.h"
#include "model\ModelMapRepository.h"
#include "MapView.h"
#include "ModelFactory.h"
#include "model\ModelMapFactory.h"

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
}

void GameFactory::CreateNewGame()
{
	if( nullptr == MapViewInstance )
	{
		Q_ASSERT(MapViewInstance);
		return;
	}

	ModelMapFactory::GetInstance()->CreateModelMap();

	MapViewInstance->Create();
}

void GameFactory::SetMapView( MapView* mapView )
{
	MapViewInstance = mapView;
}

