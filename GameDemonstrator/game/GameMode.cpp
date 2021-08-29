#include "stdafx.h"
#include "GameMode.h"
#include "LogInterface.h"
#include "GameDemonstrator.h"
#include "ActionRepository.h"

QMenu*		GameMode::GameModeChangeMenu = nullptr;

GameMode::GameMode(GameDemonstrator* gameDemonstrator)
	: GameDemonstratorObject(gameDemonstrator),
	MapViewObject(nullptr)
{
}

GameMode::~GameMode()
{
}

bool GameMode::Init()
{
	if (nullptr == GameDemonstratorObject)
	{
		Q_ASSERT(GameDemonstratorObject);
		jha::GetLog()->Log_WARNING(tr("Member <GameDemonstrator> must not be null!"));
		return false;
	}

	if (nullptr == MapViewObject)
	{
		Q_ASSERT(MapViewObject);
		jha::GetLog()->Log_WARNING(tr("Member <MapView> must not be null!"));
		return false;
	}

	CreateGameModeChangeMenu();

	return DoInit();
}

void GameMode::CreateGameModeChangeMenu()
{
	if (nullptr != GameModeChangeMenu)
	{
		return;
	}
	GameModeChangeMenu = GameDemonstratorObject->menuBar()->addMenu(tr("&GameMode"));
	CreateMenuEntryEditor();
	CreateMenuEntrySinglePlayer();

}

void GameMode::CreateMenuEntryEditor()
{
	QIcon iconModeEditor(QPixmap(".//Resources//gear_edit.ico"));
	QAction* modeEditorAction = new QAction(iconModeEditor, tr("&Editor"), this);
	modeEditorAction->setStatusTip(tr("Open editor"));
	ActionRepository::GetInstance()->AddAction(modeEditorAction);
	GameModeChangeMenu->addAction(modeEditorAction);
	//	connect(modeEditorAction, &QAction::triggered, ConnectorLoadCreateGameInstance, &ConnectorLoadCreateGame::SlotCreateNewGame, Qt::QueuedConnection);
}

void GameMode::CreateMenuEntrySinglePlayer()
{
	QIcon iconModeSinglePlayer(QPixmap(".//Resources//joystick.ico"));
	QAction* modeSinglePlayerAction = new QAction(iconModeSinglePlayer, tr("&Single player"), this);
	modeSinglePlayerAction->setStatusTip(tr("Open single player"));
	ActionRepository::GetInstance()->AddAction(modeSinglePlayerAction);
	GameModeChangeMenu->addAction(modeSinglePlayerAction);
	//	connect(modeSinglePlayerAction, &QAction::triggered, ConnectorLoadCreateGameInstance, &ConnectorLoadCreateGame::SlotCreateNewGame, Qt::QueuedConnection);
}
