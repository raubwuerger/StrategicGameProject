#include "stdafx.h"
#include "CommandCreateNewGame.h"
#include "dialogs\CreateNewGameDialog.h"
#include "game\GameConfig.h"
#include "game\GameOwnerRepository.h"
#include "gameController\GameFactory.h"
#include "map\MapHexItemFactory.h"
#include "map\MapUnitItemFactory.h"

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

	int owner = dialog->GetOwnerTypeId();
	int opponents = dialog->GetOpponentCount();
	int difficulty = dialog->GetDifficultyLevel();

	GameConfig::MapRows = rows;
	GameConfig::MapCols = cols;
	GameConfig::Player = const_cast<GameOwner*>(GameOwnerRepository::GetInstance()->GetById(owner));
	GameConfig::DifficultyLevel = difficulty;
	GameConfig::PlayerCount = (opponents + 1);
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
	return mapUnitItemFactory.Create(mapView);
}
