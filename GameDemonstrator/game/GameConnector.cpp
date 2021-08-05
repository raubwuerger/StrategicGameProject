#include "stdafx.h"
#include "GameConnector.h"
#include "model\ModelMapRepository.h"
#include "MapView.h"
#include "ModelFactory.h"
#include "SerializerFactory.h"
#include "SerializerInterface.h"
#include ".\model\ModelMapFactory.h"

GameConnector::GameConnector()
{
}

GameConnector::~GameConnector()
{
}

void GameConnector::CreateNewGame()
{
	if( nullptr == MapViewInstance )
	{
		Q_ASSERT(MapViewInstance);
		return;
	}

	ModelMapFactory factory;
	factory.CreateModelMap();

	MapViewInstance->Create();
}

void GameConnector::LoadSaveGame()
{
	if( nullptr == MapViewInstance )
	{
		Q_ASSERT(MapViewInstance);
		return;
	}

	SerializerFactory().CreateInterface()->LoadGame();

	MapViewInstance->Create();
}

void GameConnector::SetMapView( MapView* mapView )
{
	MapViewInstance = mapView;
}

