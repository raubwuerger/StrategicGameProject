// ID: $Id: config.properties,v 1.6 2006/10/05 08:51:42 jha Exp $
//--------------------------------

#include "stdafx.h"
#include "GameModeSinglePlayer.h"
#include "dialogs\GameTurnDialog.h"
#include "dialogs\GameUnitInfoDialog.h"
#include "GameDemonstrator.h"
#include "dialogs/CreateNewGameDialog.h"
#include "ActionRepository.h"
#include "GameFactory.h"
#include "GameConfig.h"
#include "map\MapHexItemFactory.h"
#include "map\MapUnitItemFactory.h"
#include "map\MapCityItemFactory.h"
#include "model\ModelOwnerTypeRepository.h"
#include "map\MapView.h"
#include "GameInfoDialogController.h"
#include "GameTurnController.h"

//=================================================================================================
GameModeSinglePlayer::GameModeSinglePlayer(GameDemonstrator* gameDemonstrator)
	: GameMode(gameDemonstrator),
		GameMenu(nullptr),
		MenuTitle("&Game"),
		GameInfoDialogControllerObject(nullptr),
		GameTurnControllerObject(nullptr)
{

}

//=================================================================================================
bool GameModeSinglePlayer::DoInit()
{
	CreateGameMenu();
	CreateMenuEntries();

	HideDockWidgets();
	HideMenu();
	return true;
}

//=================================================================================================
void GameModeSinglePlayer::CreateGameMenu()
{
	GameMenu = GameDemonstratorObject->menuBar()->addMenu(MenuTitle);
}

//=================================================================================================
void GameModeSinglePlayer::Activate(int type)
{
	ShowDockWidgets();
	ShowMenu();
}

//=================================================================================================
void GameModeSinglePlayer::Deactivate(int type)
{
	HideMenu();
	HideDockWidgets();
}

//=================================================================================================
void GameModeSinglePlayer::ShowMenu()
{
	if (nullptr != GameMenu)
	{
		GameMenu->setTitle(MenuTitle);
	}
}

//=================================================================================================
void GameModeSinglePlayer::HideMenu()
{
	if (nullptr != GameMenu)
	{
		GameMenu->setTitle(QString(""));
	}
}

//=================================================================================================
void GameModeSinglePlayer::ShowDockWidgets()
{
	GameInfoDialogControllerObject->ShowDockWidgets();
}

//=================================================================================================
void GameModeSinglePlayer::CreateMenuEntries()
{
	QIcon next(QPixmap(".//Resources//media_end.ico"));
	QAction* nextTurnAction = new QAction(next, tr("&Next turn"), this);
	nextTurnAction->setStatusTip(tr("Next turn"));
	connect(nextTurnAction, &QAction::triggered, GameTurnControllerObject, &GameTurnController::SlotStartNextTurn, Qt::QueuedConnection);
	GameMenu->addAction(nextTurnAction);
	ActionRepository::GetInstance()->AddAction(nextTurnAction);
}

//=================================================================================================
void GameModeSinglePlayer::HideDockWidgets()
{
	GameInfoDialogControllerObject->HideDockWidgets();
}

//=================================================================================================
void GameModeSinglePlayer::LoadSaveGame()
{
	QString savegameName;
	if (false == LoadGame(savegameName))
	{
		GameDemonstratorObject->ShowGameMainDialog();
		return;
	}
}

//=================================================================================================
bool GameModeSinglePlayer::ShowCreateNewGameDialog()
{
	CreateNewGameDialog* dialog = new CreateNewGameDialog();
	if (QDialog::Accepted == dialog->exec())
	{
		GetGameCreationData(dialog);
		return true;
	}
	return false;
}

//=================================================================================================
bool GameModeSinglePlayer::GetGameCreationData(CreateNewGameDialog* dialog)
{
	int rows = dialog->GetTilesRows();
	int cols = dialog->GetTilesCols();

	int owner = dialog->GetOwnerTypeId();
	int opponents = dialog->GetOpponentCount();
	int diffuclty = dialog->GetDifficultyLevel();

	GameConfig::MapRows = rows;
	GameConfig::MapCols = cols;
	GameConfig::PlayerOwnerType = const_cast<ModelOwnerType*>(ModelOwnerTypeRepository::GetInstance()->GetOwnerTypeById(owner));

	GameFactory gameFactory;
	gameFactory.Create();

	MapHexItemFactory mapHexItemFactory;
	mapHexItemFactory.Create(MapViewObject);

	MapUnitItemFactory mapUnitItemFactory;
	mapUnitItemFactory.Create(MapViewObject);

	return false;
}

//=================================================================================================
void GameModeSinglePlayer::CreateNewGame()
{
	if (false == ShowCreateNewGameDialog())
	{
		GameDemonstratorObject->ShowGameMainDialog();
		return;
	}
}
//=================================================================================================
bool GameModeSinglePlayer::LoadGame(QString& savegameName)
{
	savegameName = QFileDialog::getOpenFileName(GameDemonstratorObject, tr("Open Save Game"), "./savegames", tr("Savegame files (*.xml )"));
	if (true == savegameName.isNull())
	{
		return false;
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

	return true;
}
