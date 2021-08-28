// ID: $Id: config.properties,v 1.6 2006/10/05 08:51:42 jha Exp $
//--------------------------------

#include "stdafx.h"
#include "GameModeSinglePlayer.h"
#include "dialogs\GameTurnDialog.h"
#include "GameDemonstrator.h"

//=================================================================================================
GameModeSinglePlayer::GameModeSinglePlayer(GameDemonstrator* gameDemonstrator)
	: GameMode(gameDemonstrator),
	GameTurnDialogInstance(nullptr),
	GameMenu(nullptr)
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
	GameMenu = GameDemonstratorObject->menuBar()->addMenu(tr("&Game"));
	CreateGameTurnInfoDialog();
}

//=================================================================================================
void GameModeSinglePlayer::Deavtivate()
{
}

//=================================================================================================
void GameModeSinglePlayer::CreateGameTurnInfoDialog()
{
	QDockWidget *dockCountry = new QDockWidget(tr("Game turn"), GameDemonstratorObject);
	dockCountry->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	GameTurnDialogInstance = new GameTurnDialog(dockCountry);
	dockCountry->setWidget(GameTurnDialogInstance);
	GameDemonstratorObject->addDockWidget(Qt::RightDockWidgetArea, dockCountry);
	GameMenu->addAction(dockCountry->toggleViewAction());
}

