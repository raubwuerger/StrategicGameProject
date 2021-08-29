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
	GameTurnDialogInstance = new GameTurnDialog();
	return true;
}

//=================================================================================================
void GameModeSinglePlayer::Activate()
{
	CreateGameTurnInfoDialog();
	ShowCreateNewGameDialog();
}

//=================================================================================================
void GameModeSinglePlayer::Deavtivate()
{
	if (nullptr != GameTurnDialogInstance)
	{
		GameTurnDialogInstance->hide();
	}
}

//=================================================================================================
void GameModeSinglePlayer::CreateGameTurnInfoDialog()
{
	if (nullptr != GameTurnDialogInstance)
	{
		return;
	}
	QDockWidget *dockCountry = new QDockWidget(tr("Game turn"), GameDemonstratorObject);
	dockCountry->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	GameTurnDialogInstance = new GameTurnDialog(dockCountry);
	dockCountry->setWidget(GameTurnDialogInstance);
	GameDemonstratorObject->addDockWidget(Qt::RightDockWidgetArea, dockCountry);
}

//=================================================================================================
void GameModeSinglePlayer::ShowCreateNewGameDialog()
{
	CreateNewGameDialog* dialog = new CreateNewGameDialog();
	dialog->exec();
}

