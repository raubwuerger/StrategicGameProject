// ID: $Id: config.properties,v 1.6 2006/10/05 08:51:42 jha Exp $
//--------------------------------

#include "stdafx.h"
#include "GameModeSinglePlayer.h"
#include "dialogs\GameTurnDialog.h"
#include "GameDemonstrator.h"
#include "dialogs/CreateNewGameDialog.h"

//=================================================================================================
GameModeSinglePlayer::GameModeSinglePlayer(GameDemonstrator* gameDemonstrator)
	: GameMode(gameDemonstrator),
	GameTurnDialogInstance(nullptr)
{

}

//=================================================================================================
bool GameModeSinglePlayer::DoInit()
{
	return true;
}

//=================================================================================================
void GameModeSinglePlayer::Activate(int type)
{
	if( false == ShowCreateNewGameDialog() )
	{
		GameDemonstratorObject->ShowGameMainDialog();
		return;
	}
	ShowGameTurnInfoDialog();
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
	ShowGameTurnInfoDialog();
}

//=================================================================================================
void GameModeSinglePlayer::ShowGameTurnInfoDialog()
{
	if (nullptr != GameTurnDialogInstance)
	{
		GameTurnDialogInstance->show();
	}
}

//=================================================================================================
void GameModeSinglePlayer::Deactivate(int type)
{
	if (nullptr != GameTurnDialogInstance)
	{
		GameTurnDialogInstance->hide();
	}
}

//=================================================================================================
void GameModeSinglePlayer::CreateGameTurnInfoDialog()
{
	GameTurnDialogInstance = new GameTurnDialog();
	QDockWidget *dockCountry = new QDockWidget(tr("Game turn"), GameDemonstratorObject);
	dockCountry->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	GameTurnDialogInstance = new GameTurnDialog(dockCountry);
	dockCountry->setWidget(GameTurnDialogInstance);
	GameDemonstratorObject->addDockWidget(Qt::RightDockWidgetArea, dockCountry);
	GameTurnDialogInstance->hide();
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

