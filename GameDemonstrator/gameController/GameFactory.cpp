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
#include "gameController\GameConfig.h"

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

void GameFactory::SetDefaultOwnerType()
{
	GameConfig::Player = const_cast<GameOwnerItem*>(GameOwnerItemRepository::GetInstance()->GetDefaultOwnerType());
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

	SetDefaultOwnerType();

	if (false == GameControllerObject->InitGame())
	{
		return false;
	}
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
