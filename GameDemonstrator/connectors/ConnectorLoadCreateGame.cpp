#include "stdafx.h"
#include "ConnectorLoadCreateGame.h"
#include "model\ModelMapRepository.h"
#include ".\map\MapView.h"
#include "ModelFactory.h"
#include "io\SerializerFactory.h"
#include "io\SerializerInterface.h"
#include ".\model\ModelMapFactory.h"

ConnectorLoadCreateGame::ConnectorLoadCreateGame()
{
}

ConnectorLoadCreateGame::~ConnectorLoadCreateGame()
{
}

void ConnectorLoadCreateGame::CreateNewGame()
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

void ConnectorLoadCreateGame::LoadSaveGame()
{
	if( nullptr == MapViewInstance )
	{
		Q_ASSERT(MapViewInstance);
		return;
	}

	SerializerFactory().CreateInterface()->LoadGame();

	MapViewInstance->Create();
}

void ConnectorLoadCreateGame::SetMapView( MapView* mapView )
{
	MapViewInstance = mapView;
}

