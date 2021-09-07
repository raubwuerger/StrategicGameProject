#include "stdafx.h"
#include "GameUnitProduction.h"

GameUnitProduction::GameUnitProduction(int gameCityItemId) 
	: GameCityId(gameCityItemId),
	GameUnitId(NOT_INITIALIZED_INT),
	ProductionProgress(NOT_INITIALIZED_INT)
{

}

int GameUnitProduction::GetGameCityId() const
{
	return GameCityId;
}

void GameUnitProduction::SetGameUnitId(int gameUnitId)
{
	if (GameUnitId != gameUnitId)
	{
		ClearProductionProgress();
	}
	GameUnitId = gameUnitId;
}

void GameUnitProduction::CancelGameUnitProduction()
{
	SetGameUnitId(NOT_INITIALIZED_INT);
}

int GameUnitProduction::GetGameUnitId() const
{
	return GameUnitId;
}

void GameUnitProduction::UpdateProductionProgress(int updateValue)
{
	ProductionProgress += updateValue;
}

void GameUnitProduction::ClearProductionProgress()
{
	ProductionProgress = 0;
}

int GameUnitProduction::GetProductionProgress() const
{
	return ProductionProgress;
}

bool GameUnitProduction::IsGameUnitInProduction() const
{
	return GameUnitId != NOT_INITIALIZED_INT;
}
