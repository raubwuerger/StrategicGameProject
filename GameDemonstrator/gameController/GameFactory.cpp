#include "stdafx.h"
#include "GameFactory.h"
#include "game\GameMapItemFactory.h"
#include "io\SerializerFactory.h"
#include "io\SerializerGame.h"
#include "gameController\GameController.h"

GameController* GameFactory::GameControllerObject = nullptr;

GameFactory::GameFactory()
{
	InitGameController();
}

void GameFactory::InitGameController()
{
	if (nullptr != GameControllerObject)
	{
		return;
	}
	GameControllerObject = new GameController();
	GameControllerObject->Init();
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
