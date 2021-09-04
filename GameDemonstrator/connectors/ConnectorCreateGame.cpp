#include "stdafx.h"
#include "ConnectorCreateGame.h"
#include "gameController\GameFactory.h"
#include "map\MapView.h"
#include "map\MapHexItemFactory.h"
#include "map\MapUnitItemFactory.h"
#include "map\MapCityItemFactory.h"
#include "dialogs\CreateNewGameDialog.h"
#include "gameController\GameConfig.h"

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

	CreateNewGameDialog* dialog = new CreateNewGameDialog();
	dialog->OnlyShowMapDimensions();
	if (QDialog::Rejected == dialog->exec())
	{
		return;
	}

	GetGameCreationData(dialog);

	GameFactory gameFactory;
	gameFactory.Create();

	MapHexItemFactory mapHexItemFactory;
	mapHexItemFactory.Create(MapViewObject);

	MapUnitItemFactory mapUnitItemFactory;
	mapUnitItemFactory.Create(MapViewObject);

	MapCityItemFactory mapCityItemFactory;
	mapCityItemFactory.Create(MapViewObject);
}

void ConnectorCreateGame::GetGameCreationData(const CreateNewGameDialog* dialog)
{
	GameConfig::MapRows = dialog->GetTilesRows();
	GameConfig::MapCols = dialog->GetTilesCols();
}
