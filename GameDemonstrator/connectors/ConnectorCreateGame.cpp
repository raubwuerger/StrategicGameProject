#include "stdafx.h"
#include "ConnectorCreateGame.h"
#include "gameController\GameFactory.h"
#include "map\MapView.h"
#include "map\MapHexItemFactory.h"
#include "map\MapUnitItemFactory.h"
#include "map\MapCityItemFactory.h"

ConnectorCreateGame::ConnectorCreateGame()
	: MapViewObject(nullptr)
{
}

void ConnectorCreateGame::SlotCreateNewGame()
{
	if( nullptr == MapViewObject )
	{
		Q_ASSERT(MapViewObject);
		return;
	}

	GameFactory gameFactory;
	gameFactory.Create();

	MapHexItemFactory mapHexItemFactory;
	mapHexItemFactory.Create(MapViewObject);

	MapUnitItemFactory mapUnitItemFactory;
	mapUnitItemFactory.Create(MapViewObject);

	MapCityItemFactory mapCityItemFactory;
	mapCityItemFactory.Create(MapViewObject);
}
