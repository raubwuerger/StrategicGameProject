// ID: $Id: config.properties,v 1.6 2006/10/05 08:51:42 jha Exp $
//--------------------------------

#include "stdafx.h"
#include "GameModeSinglePlayer.h"
#include "dialogs\GameTurnDialog.h"
#include "GameDemonstrator.h"
#include "dialogs/CreateNewGameDialog.h"
#include "ActionRepository.h"
#include "GameFactory.h"
#include "GameConfig.h"
#include "map\MapHexItemFactory.h"
#include "map\MapUnitItemFactory.h"
#include "map\MapCityItemFactory.h"
#include "model\ModelOwnerTypeRepository.h"

//=================================================================================================
GameModeSinglePlayer::GameModeSinglePlayer(GameDemonstrator* gameDemonstrator)
	: GameMode(gameDemonstrator),
	GameTurnDialogInstance(nullptr),
	GameMenu(nullptr),
	MenuTitle("&Game")
{

}

//=================================================================================================
bool GameModeSinglePlayer::DoInit()
{
	CreateGameTurnInfoDialog();
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
void GameModeSinglePlayer::CreateGameTurnInfoDialog()
{
	QDockWidget *dockTurnInfoDialog = new QDockWidget(tr("Game turn"), GameDemonstratorObject);
	dockTurnInfoDialog->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	GameTurnDialogInstance = new GameTurnDialog(dockTurnInfoDialog);
	dockTurnInfoDialog->setWidget(GameTurnDialogInstance);
	GameDemonstratorObject->addDockWidget(Qt::RightDockWidgetArea, dockTurnInfoDialog);

	DockWidgets.push_back(dockTurnInfoDialog);
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
	QVectorIterator<QDockWidget*> dockWidgets(DockWidgets);
	while (dockWidgets.hasNext())
	{
		dockWidgets.next()->show();
	}
}

//=================================================================================================
void GameModeSinglePlayer::CreateMenuEntries()
{
	QIcon next(QPixmap(".//Resources//media_end.ico"));
	QAction* nextTurnAction = new QAction(next, tr("&Next turn"), this);
	nextTurnAction->setStatusTip(tr("Next turn"));
//	connect(nextTurnAction, &QAction::triggered, MainGameLoopInstance, &GameMainLoop::SlotStep, Qt::QueuedConnection);
	GameMenu->addAction(nextTurnAction);
	ActionRepository::GetInstance()->AddAction(nextTurnAction);
}

//=================================================================================================
void GameModeSinglePlayer::HideDockWidgets()
{
	QVectorIterator<QDockWidget*> dockWidgets(DockWidgets);
	while (dockWidgets.hasNext())
	{
		dockWidgets.next()->hide();
	}
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
	CreateGameTurnInfoDialog();
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
	GameConfig::OwnerType = const_cast<ModelOwnerType*>(ModelOwnerTypeRepository::GetInstance()->GetOwnerTypeById(owner));

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
	savegameName = QFileDialog::getOpenFileName(GameDemonstratorObject, tr("Open Save Game"), "./savegames", tr("Image Files (*.xml )"));
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

