#include "stdafx.h"
#include "CommandCreateNewGame.h"
#include "dialogs\CreateNewGameDialog.h"
#include "game\GameConfig.h"
#include "game\GameOwnerRepository.h"
#include "gameController\GameFactory.h"
#include "map\MapHexItemFactory.h"
#include "map\MapUnitItemFactory.h"
#include "map\MapCityItemFactory.h"

bool CommandCreateNewGame::Create(MapView* mapView)
{
	CreateNewGameDialog* dialog = new CreateNewGameDialog();
	if (QDialog::Rejected == dialog->exec())
	{
		return false;
	}

	GetGameCreationData(dialog);
	return CreateNewGame(mapView);
}

void CommandCreateNewGame::GetGameCreationData(const CreateNewGameDialog* dialog)
{
	int rows = dialog->GetTilesRows();
	int cols = dialog->GetTilesCols();
	const int OWNER_TYPE_ID_OFFSET = 2;

	int owner = dialog->GetOwnerTypeId() + OWNER_TYPE_ID_OFFSET;
	int opponents = dialog->GetOpponentCount();
	int difficulty = dialog->GetDifficultyLevel();
	QString mapType = dialog->GetMapType();

	GameConfig::MapRows = rows;
	GameConfig::MapCols = cols;
	GameConfig::Player = const_cast<GameOwner*>(GameOwnerRepository::GetInstance()->GetById(owner));
	GameConfig::PlayerId = owner;
	GameConfig::DifficultyLevel = difficulty;
	GameConfig::PlayerCount = (opponents + 1);
	GameConfig::MapType = mapType;
}

bool CommandCreateNewGame::CreateNewGame(MapView* mapView)
{
	GameFactory gameFactory;
	if (false == gameFactory.Create())
	{
		return false;
	}

	MapHexItemFactory mapHexItemFactory;
	if (false == mapHexItemFactory.Create(mapView))
	{
		return false;
	}

	MapUnitItemFactory mapUnitItemFactory;
	if (false == mapUnitItemFactory.Create(mapView))
	{
		return false;
	}

	MapCityItemFactory mapCityItemFactory;
	return mapCityItemFactory.Create(mapView);
}
