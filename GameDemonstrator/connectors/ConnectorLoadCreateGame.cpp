#include "stdafx.h"
#include "ConnectorLoadCreateGame.h"
#include "game\GameMapRepository.h"
#include ".\map\MapView.h"
#include "ModelFactory.h"
#include "io\SerializerFactory.h"
#include "io\SerializerGame.h"
#include ".\game\GameMapFactory.h"

ConnectorLoadCreateGame::ConnectorLoadCreateGame()
{
}

ConnectorLoadCreateGame::~ConnectorLoadCreateGame()
{
}

void ConnectorLoadCreateGame::SlotCreateNewGame()
{
	if( nullptr == MapViewInstance )
	{
		Q_ASSERT(MapViewInstance);
		return;
	}

	GameMapFactory factory;
	factory.CreateModelMap();

	MapViewInstance->Create();
}

void ConnectorLoadCreateGame::SlotLoadSaveGame()
{
	if( nullptr == MapViewInstance )
	{
		Q_ASSERT(MapViewInstance);
		return;
	}

	SerializerFactory().CreateInterface()->SlotLoadGame();

	MapViewInstance->Create();
}

void ConnectorLoadCreateGame::SetMapView( MapView* mapView )
{
	MapViewInstance = mapView;
}

