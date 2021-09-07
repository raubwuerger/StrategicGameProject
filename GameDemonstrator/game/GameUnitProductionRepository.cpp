#include "stdafx.h"
#include "GameUnitProductionRepository.h"
#include "LogInterface.h"

GameUnitProductionRepository* GameUnitProductionRepository::Instance = nullptr;

GameUnitProductionRepository* GameUnitProductionRepository::GetInstance()
{
	if ( nullptr != Instance )
	{
		return Instance;
	}

	Instance = new GameUnitProductionRepository();
	return Instance;
}

bool GameUnitProductionRepository::RegisterGameUnitProduction(GameUnitProduction* gameUnitProduction)
{
	Q_ASSERT(gameUnitProduction);
	if (nullptr == gameUnitProduction)
	{
		return false;
	}
	return false;
}

bool GameUnitProductionRepository::Init()
{
	return true;
}

void GameUnitProductionRepository::Release()
{
	delete Instance;
	Instance = nullptr;
}

GameUnitProductionRepository::GameUnitProductionRepository()
{

}
