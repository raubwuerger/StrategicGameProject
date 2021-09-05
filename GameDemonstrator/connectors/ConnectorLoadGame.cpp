#include "stdafx.h"
#include "ConnectorLoadGame.h"
#include "GameDemonstrator.h"
#include "game/GameConfig.h"
#include "gameController/GameFactory.h"
#include "map/MapHexItemFactory.h"
#include "map/MapUnitItemFactory.h"
#include "map/MapCityItemFactory.h"

ConnectorLoadGame::ConnectorLoadGame()
	: MapViewObject(nullptr),
	GameDemonstratorObject(nullptr)
{

}

void ConnectorLoadGame::SlotLoadGame()
{
	Q_ASSERT(MapViewObject);
	Q_ASSERT(GameDemonstratorObject);

	QString savegameName = QFileDialog::getOpenFileName(GameDemonstratorObject, tr("Open Save Game"), "./savegames", tr("Savegame files (*.xml )"));
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
