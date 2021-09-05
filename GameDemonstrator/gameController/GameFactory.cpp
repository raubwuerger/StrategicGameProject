#include "stdafx.h"
#include "GameFactory.h"
#include "game\GameMapItemFactory.h"
#include "io\SerializerFactory.h"
#include "io\SerializerGame.h"
#include "GameUnitController.h"
#include "GameModeController.h"
#include "GameInfoDialogController.h"
#include "GameTurnController.h"
#include "game\GameOwnerItemFactory.h"
#include "game\GameOwnerItemRepository.h"
#include "game/GameUnitItemFactory.h"
#include "GameConfig.h"
#include "GameObjectController.h"
#include "dialogs\GameTurnDialog.h"

GameUnitController* GameFactory::GameControllerObject = nullptr;
GameModeController*	GameFactory::GameModeControllerObject = nullptr;
GameDemonstrator*	GameFactory::GameDemonstratorObject = nullptr;
GameTurnController* GameFactory::GameTurnControllerObject = nullptr;

MapView*			GameFactory::MapViewObject = nullptr;
GameMainDialog*		GameFactory::GameMainDialogObject = nullptr;
GameInfoDialogController*	GameFactory::GameInfoDialogControllerObject = nullptr;

GameFactory::GameFactory()
{
	InitGameTurnController();
	InitGameInfoDialogController();
	InitGameController();
	InitGameModeController();
	InitSignalConnections();
}

void GameFactory::InitGameController()
{
	if (nullptr != GameControllerObject)
	{
		return;
	}
	GameControllerObject = new GameUnitController();
	GameControllerObject->Init();
}

void GameFactory::InitGameModeController()
{
	if (nullptr != GameModeControllerObject)
	{
		return;
	}
	GameModeControllerObject = new GameModeController;
	GameModeControllerObject->MapViewObject = MapViewObject;
	GameModeControllerObject->GameMainDialogObject = GameMainDialogObject;
	GameModeControllerObject->GameControllerObject = GameControllerObject;
	GameModeControllerObject->GameInfoDialogControllerObject = GameInfoDialogControllerObject;
	GameModeControllerObject->GameTurnControllerObject = GameTurnControllerObject;
	GameModeControllerObject->Init(GameDemonstratorObject);
}

void GameFactory::InitGameInfoDialogController()
{
	if (nullptr != GameInfoDialogControllerObject)
	{
		return;
	}

	GameInfoDialogControllerObject = new GameInfoDialogController;
	GameInfoDialogControllerObject->GameDemonstratorObject = GameDemonstratorObject;
	GameInfoDialogControllerObject->MapViewObject = MapViewObject;
	GameInfoDialogControllerObject->Init();
}

void GameFactory::InitGameTurnController()
{
	GameTurnControllerObject = new GameTurnController();
}

void GameFactory::SetDefaultGameValues()
{
	GameConfig::Player = const_cast<GameOwnerItem*>(GameOwnerItemRepository::GetInstance()->GetDefaultOwnerType());
	GameConfig::CurrentTurn = 1;
}

void GameFactory::InitSignalConnections()
{
	QObject::connect(GameTurnControllerObject, &GameTurnController::SignalUpdateTurnDialog, GameInfoDialogControllerObject, &GameInfoDialogController::SlotShowTurnInfoDialog);
	QObject::connect(GameTurnControllerObject, &GameTurnController::SignalUpdateTurnObjects, GameObjectController::GetInstance(), &GameObjectController::SlotDoUpdateTurn);
}

bool GameFactory::Create()
{
	GameMapItemFactory factory;
	if (false == factory.Create())
	{
		return false;
	}

	GameOwnerItemFactory ownerFactory;
	if (false == ownerFactory.Create())
	{
		return false;
	}

	GameUnitItemFactory unitFactory;
	if (false == unitFactory.Init())
	{
		return false;
	}

	SetDefaultGameValues();

	if (false == GameControllerObject->InitGame())
	{
		return false;
	}
	emit GameTurnControllerObject->SignalUpdateTurnDialog();
	return true;
}

bool GameFactory::CreateFromSavegame()
{
	bool gameLoaded = SerializerFactory().CreateInterface()->LoadGame();
	if (false == gameLoaded)
	{
		return false;
	}
	if (false == GameControllerObject->InitGame())
	{
		return false;
	}
	emit GameTurnControllerObject->SignalUpdateTurnDialog();
	return true;
}
