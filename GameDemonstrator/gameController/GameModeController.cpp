#include "stdafx.h"
#include "GameModeController.h"
#include "ActionRepository.h"
#include "GameDemonstrator.h"
#include "gameController/GameMode.h"
#include "gameController/GameModeEditor.h"
#include "gameController/GameModeSinglePlayer.h"
#include "map/MapView.h"
#include "dialogs/GameMainDialog.h"

QMenu*		GameModeController::GameModeChangeMenu = nullptr;

GameModeController::GameModeController()
	: MapViewObject(nullptr)
{

}

bool GameModeController::Init(GameDemonstrator* gameDemonstrator)
{
	CreateGameModes(gameDemonstrator);
	CreateMenuEntries(gameDemonstrator);
	return true;
}

void GameModeController::CreateGameModes(GameDemonstrator* gameDemonstrator)
{
	GameModeEditorObject = new GameModeEditor(gameDemonstrator);
	GameModeEditorObject->MapViewObject = MapViewObject;
	if (false == GameModeEditorObject->Init())
	{
		return;
	}
	QObject::connect(GameMainDialogObject->StartEditor, &QPushButton::clicked, GameModeEditorObject, &GameMode::Activate);


	GameModeSinglePlayerObject = new GameModeSinglePlayer(gameDemonstrator);
	GameModeSinglePlayerObject->MapViewObject = MapViewObject;
	if (false == GameModeSinglePlayerObject->Init())
	{
		return;
	}
	QObject::connect(GameMainDialogObject->StartSingleplayer, &QPushButton::clicked, GameModeSinglePlayerObject, &GameMode::Activate);


	QObject::connect(GameMainDialogObject->StartEditor, &QPushButton::clicked, GameModeSinglePlayerObject, &GameMode::Deavtivate);
	QObject::connect(GameMainDialogObject->StartSingleplayer, &QPushButton::clicked, GameModeEditorObject, &GameMode::Deavtivate);
}

void GameModeController::CreateMenuEntries(GameDemonstrator* gameDemonstrator)
{
	if (nullptr != GameModeChangeMenu)
	{
		return;
	}
	GameModeChangeMenu = gameDemonstrator->menuBar()->addMenu(QObject::tr("&GameMode"));
	CreateMenuEntryEditor(gameDemonstrator);
	CreateMenuEntrySinglePlayer(gameDemonstrator);
}

void GameModeController::CreateMenuEntryEditor(GameDemonstrator* gameDemonstrator)
{
	QIcon iconModeEditor(QPixmap(".//Resources//gear_edit.ico"));
	QAction* modeEditorAction = new QAction(iconModeEditor, QObject::tr("&Editor"), gameDemonstrator);
	modeEditorAction->setStatusTip(QObject::tr("Open editor"));
	ActionRepository::GetInstance()->AddAction(modeEditorAction);
	GameModeChangeMenu->addAction(modeEditorAction);
	//	connect(modeEditorAction, &QAction::triggered, ConnectorLoadCreateGameInstance, &ConnectorLoadCreateGame::SlotCreateNewGame, Qt::QueuedConnection);
}

void GameModeController::CreateMenuEntrySinglePlayer(GameDemonstrator* gameDemonstrator)
{
	QIcon iconModeSinglePlayer(QPixmap(".//Resources//joystick.ico"));
	QAction* modeSinglePlayerAction = new QAction(iconModeSinglePlayer, QObject::tr("&Single player"), gameDemonstrator);
	modeSinglePlayerAction->setStatusTip(QObject::tr("Open single player"));
	ActionRepository::GetInstance()->AddAction(modeSinglePlayerAction);
	GameModeChangeMenu->addAction(modeSinglePlayerAction);
	//	connect(modeSinglePlayerAction, &QAction::triggered, ConnectorLoadCreateGameInstance, &ConnectorLoadCreateGame::SlotCreateNewGame, Qt::QueuedConnection);
}
