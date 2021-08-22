#include "stdafx.h"
#include "ConnectorLoadCreateGame.h"
#include "game\GameMapItemRepository.h"
#include ".\map\MapView.h"
#include "ModelFactory.h"
#include "io\SerializerFactory.h"
#include "io\SerializerGame.h"
#include ".\game\GameMapItemFactory.h"
#include "game\GameFactory.h"
#include "game\GameConfig.h"
#include "map\MapHexItemFactory.h"
#include "map\MapUnitItemFactory.h"
#include "map\MapCityItemFactory.h"

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

	MapHexItemFactory mapHexItemFactory;
	mapHexItemFactory.Create(MapViewInstance);

	MapUnitItemFactory mapUnitItemFactory;
	mapUnitItemFactory.Create(MapViewInstance);
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

	MapHexItemFactory mapHexItemFactory;
	mapHexItemFactory.Create(MapViewInstance);

	MapUnitItemFactory mapUnitItemFactory;
	mapUnitItemFactory.Create(MapViewInstance);

	MapCityItemFactory mapCityItemFactory;
	mapCityItemFactory.Create(MapViewInstance);
}

void ConnectorLoadCreateGame::SetMapView( MapView* mapView )
{
	MapViewInstance = mapView;
}

