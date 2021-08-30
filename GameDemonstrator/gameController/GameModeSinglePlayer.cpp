// ID: $Id: config.properties,v 1.6 2006/10/05 08:51:42 jha Exp $
//--------------------------------

#include "stdafx.h"
#include "GameModeSinglePlayer.h"
#include "dialogs\GameTurnDialog.h"
#include "GameDemonstrator.h"
#include "dialogs/CreateNewGameDialog.h"
#include "ActionRepository.h"

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
	if (nullptr != GameTurnDialogInstance)
	{
		GameTurnDialogInstance->show();
	}
}

//=================================================================================================
void GameModeSinglePlayer::Activate(int type)
{
	ShowDockWidgets();
	ShowMenu();
	if (false == ShowCreateNewGameDialog())
	{
		GameDemonstratorObject->ShowGameMainDialog();
		return;
	}
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
void GameModeSinglePlayer::LoadGame()
{
	QString savegameName;
	if (false == LoadSaveGame(savegameName))
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
		CreateNewGame(dialog);
		return true;
	}
	return false;
}

//=================================================================================================
bool GameModeSinglePlayer::CreateNewGame(CreateNewGameDialog* dialog)
{
	int rows = dialog->GetTilesRows();
	int cols = dialog->GetTilesCols();

	int owner = dialog->GetOwnerTypeId();
	int opponents = dialog->GetOpponentCount();
	int diffuclty = dialog->GetDifficultyLevel();

	return false;
}

//=================================================================================================
bool GameModeSinglePlayer::LoadSaveGame(QString& savegameName)
{
	savegameName = QFileDialog::getOpenFileName(GameDemonstratorObject, tr("Open Save Game"), "./savegames", tr("Image Files (*.xml )"));
	if (true == savegameName.isNull())
	{
		return false;
	}

	return true;
}

