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
#include "game\GameConfig.h"
#include "map\MapHexItemFactory.h"
#include "map\MapUnitItemFactory.h"
#include "map\MapCityItemFactory.h"
#include "game\GameOwnerRepository.h"
#include "map\MapView.h"
#include "GameInfoDialogController.h"
#include "GameTurnController.h"
#include "RepositoryCleaner.h"
#include "command\CommandCreateNewGame.h"

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
	nextTurnAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
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
void GameModeSinglePlayer::CreateNewGame()
{
	CommandCreateNewGame commandCreateNewGame;
	if (false == commandCreateNewGame.Create(MapViewObject) )
	{
		GameDemonstratorObject->ShowGameMainDialog();
		return;
	}
}
//=================================================================================================
bool GameModeSinglePlayer::LoadGame(QString& savegameName)
{
	savegameName = QFileDialog::getOpenFileName(GameDemonstratorObject, tr("Open Save Game"), "./save games", tr("Save game files (*.xml )"));
	if (true == savegameName.isNull())
	{
		return false;
	}

	RepositoryCleaner::GetInstance()->ReleaseAll();

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
