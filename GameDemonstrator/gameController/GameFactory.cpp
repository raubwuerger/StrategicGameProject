#include "stdafx.h"
#include "GameFactory.h"
#include "game\GameMapItemFactory.h"
#include "io\SerializerFactory.h"
#include "io\SerializerGame.h"
#include "GameUnitController.h"
#include "GameModeController.h"
#include "GameInfoDialogController.h"
#include "GameTurnController.h"

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

bool GameFactory::Create()
{
	GameMapItemFactory factory;
	factory.Create();
	GameControllerObject->InitGame();
	return true;
}

bool GameFactory::CreateFromSavegame()
{
	bool gameLoaded = SerializerFactory().CreateInterface()->LoadGame();
	if (false == gameLoaded)
	{
		return false;
	}
	GameControllerObject->InitGame();
	return true;
}
