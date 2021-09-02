#include "stdafx.h"
#include "GameFactory.h"
#include "game\GameMapItemFactory.h"
#include "io\SerializerFactory.h"
#include "io\SerializerGame.h"
#include "GameUnitController.h"
#include "GameModeController.h"

GameUnitController* GameFactory::GameControllerObject = nullptr;
GameModeController*	GameFactory::GameModeControllerObject = nullptr;
GameDemonstrator*	GameFactory::GameDemonstratorObject = nullptr;
MapView*			GameFactory::MapViewObject = nullptr;
GameMainDialog*		GameFactory::GameMainDialogObject = nullptr;



GameFactory::GameFactory()
{
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
	GameModeControllerObject->Init(GameDemonstratorObject);
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
