#include "stdafx.h"
#include "GameModeController.h"
#include "ActionRepository.h"
#include "GameDemonstrator.h"
#include "gameController/GameMode.h"
#include "gameController/GameModeEditor.h"
#include "gameController/GameModeSinglePlayer.h"
#include "map/MapView.h"
#include "dialogs/GameMainDialog.h"
#include "GameUnitController.h"

QMenu*		GameModeController::GameModeChangeMenu = nullptr;

GameModeController::GameModeController()
	: MapViewObject(nullptr),
	GameControllerObject(nullptr),
	GameInfoDialogControllerObject(nullptr)
{

}

bool GameModeController::Init(GameDemonstrator* gameDemonstrator)
{
	CreateGameModes(gameDemonstrator);
	CreateMenuEntryGameMode(gameDemonstrator);
	return true;
}

void GameModeController::LoadGame()
{
	emit LoadSavedGame();
}

void GameModeController::CreateGame()
{
	emit CreateNewGame();
}

void GameModeController::SlotModeEditorActivated()
{
	GameControllerObject->ConnectEditor();
}

void GameModeController::SlotModeSinglePlayerActivated()
{
	GameControllerObject->ConnectSinglePlayer();
}

void GameModeController::CreateGameModes(GameDemonstrator* gameDemonstrator)
{
	GameModeEditorObject = new GameModeEditor(gameDemonstrator);
	GameModeEditorObject->MapViewObject = MapViewObject;
	if (false == GameModeEditorObject->Init())
	{
		return;
	}


	GameModeSinglePlayerObject = new GameModeSinglePlayer(gameDemonstrator);
	GameModeSinglePlayerObject->MapViewObject = MapViewObject;
	GameModeSinglePlayerObject->GameInfoDialogControllerObject = GameInfoDialogControllerObject;
	GameModeSinglePlayerObject->GameTurnControllerObject = GameTurnControllerObject;
	if (false == GameModeSinglePlayerObject->Init())
	{
		return;
	}

	QObject::connect(GameMainDialogObject->ui.StartEditor, &QPushButton::clicked, GameModeSinglePlayerObject, &GameMode::Deactivate);
	QObject::connect(GameMainDialogObject->ui.CreateGame, &QPushButton::clicked, GameModeEditorObject, &GameMode::Deactivate);
	QObject::connect(GameMainDialogObject->ui.LoadGame, &QPushButton::clicked, GameModeEditorObject, &GameMode::Deactivate);

	QObject::connect(GameMainDialogObject->ui.StartEditor, &QPushButton::clicked, GameModeEditorObject, &GameMode::Activate);
	QObject::connect(GameMainDialogObject->ui.CreateGame, &QPushButton::clicked, GameModeSinglePlayerObject, &GameMode::Activate);
	QObject::connect(GameMainDialogObject->ui.LoadGame, &QPushButton::clicked, GameModeSinglePlayerObject, &GameMode::Activate);

	QObject::connect(GameMainDialogObject->ui.CreateGame, &QPushButton::clicked, this, &GameModeController::CreateGame);
	QObject::connect(GameMainDialogObject->ui.LoadGame, &QPushButton::clicked, this, &GameModeController::LoadGame);

	QObject::connect(this, &GameModeController::CreateNewGame, GameModeSinglePlayerObject, &GameModeSinglePlayer::CreateNewGame);
	QObject::connect(this, &GameModeController::LoadSavedGame, GameModeSinglePlayerObject, &GameModeSinglePlayer::LoadSaveGame);

	QObject::connect(GameMainDialogObject->ui.StartEditor, &QPushButton::clicked, this, &GameModeController::SlotModeEditorActivated);
	QObject::connect(GameMainDialogObject->ui.CreateGame, &QPushButton::clicked, this, &GameModeController::SlotModeSinglePlayerActivated);
	QObject::connect(GameMainDialogObject->ui.LoadGame, &QPushButton::clicked, this, &GameModeController::SlotModeSinglePlayerActivated);
}

void GameModeController::CreateMenuEntryGameMode(GameDemonstrator* gameDemonstrator)
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

	connect(modeEditorAction, &QAction::triggered, GameModeSinglePlayerObject, &GameMode::Deactivate, Qt::QueuedConnection);
	connect(modeEditorAction, &QAction::triggered, GameModeEditorObject, &GameMode::Activate, Qt::QueuedConnection);
}

void GameModeController::CreateMenuEntrySinglePlayer(GameDemonstrator* gameDemonstrator)
{
	QIcon iconModeSinglePlayer(QPixmap(".//Resources//joystick.ico"));
	QAction* modeSinglePlayerAction = new QAction(iconModeSinglePlayer, QObject::tr("&Single player"), gameDemonstrator);
	modeSinglePlayerAction->setStatusTip(QObject::tr("Open single player"));
	ActionRepository::GetInstance()->AddAction(modeSinglePlayerAction);
	GameModeChangeMenu->addAction(modeSinglePlayerAction);

	connect(modeSinglePlayerAction, &QAction::triggered, GameModeEditorObject, &GameMode::Deactivate, Qt::QueuedConnection);
	connect(modeSinglePlayerAction, &QAction::triggered, GameModeSinglePlayerObject, &GameMode::Activate, Qt::QueuedConnection);
}
