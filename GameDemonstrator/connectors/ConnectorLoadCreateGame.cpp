#include "stdafx.h"
#include "ConnectorLoadCreateGame.h"
#include "map\MapView.h"
#include "game\GameMapItemFactory.h"
#include "gameController\GameFactory.h"
#include "gameController\GameConfig.h"
#include "map\MapHexItemFactory.h"
#include "map\MapUnitItemFactory.h"
#include "map\MapCityItemFactory.h"
#include "gamedemonstrator.h"

ConnectorLoadCreateGame::ConnectorLoadCreateGame()
	: MapViewObject(nullptr),
	GameDemonstratorObject(nullptr)
{
}

ConnectorLoadCreateGame::~ConnectorLoadCreateGame()
{
}

void ConnectorLoadCreateGame::SlotCreateNewGame()
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
}

void ConnectorLoadCreateGame::SlotLoadSaveGame()
{
	if( nullptr == MapViewObject )
	{
		Q_ASSERT(MapViewObject);
		return;
	}

	QString savegameName = QFileDialog::getOpenFileName(GameDemonstratorObject, tr("Open Save Game"), "./savegames", tr("Image Files (*.xml )"));
	if (true == savegameName.isNull())
	{
		return;
	}

	GameConfig::CurrentSaveGameName = savegameName;

	GameFactory gameFactory;
	gameFactory.CreateFromSavegame();

	MapHexItemFactory mapHexItemFactory;
	mapHexItemFactory.Create(MapViewObject);

	MapUnitItemFactory mapUnitItemFactory;
	mapUnitItemFactory.Create(MapViewObject);

	MapCityItemFactory mapCityItemFactory;
	mapCityItemFactory.Create(MapViewObject);
}
