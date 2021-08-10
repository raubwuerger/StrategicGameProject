#include "stdafx.h"
#include "ConnectorLoadCreateGame.h"
#include "game\GameMapRepository.h"
#include ".\map\MapView.h"
#include "ModelFactory.h"
#include "io\SerializerFactory.h"
#include "io\SerializerGame.h"
#include ".\game\GameMapFactory.h"
#include "game\GameFactory.h"
#include "game\GameConfig.h"

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

	GameFactory gameFactory;
	gameFactory.Create(new GameConfig());

	MapViewInstance->Create();
}

void ConnectorLoadCreateGame::SlotLoadSaveGame()
{
	if( nullptr == MapViewInstance )
	{
		Q_ASSERT(MapViewInstance);
		return;
	}

	GameFactory gameFactory;
	gameFactory.CreateFromSavegame();

	MapViewInstance->Create();
}

void ConnectorLoadCreateGame::SetMapView( MapView* mapView )
{
	MapViewInstance = mapView;
}

