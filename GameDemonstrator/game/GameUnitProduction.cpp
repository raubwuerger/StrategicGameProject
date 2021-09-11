#include "stdafx.h"
#include "GameUnitProduction.h"

GameUnitProduction::GameUnitProduction(int gameCityId) 
	: GameCityId(gameCityId),
	GameUnitId(NOT_INITIALIZED_INT),
	ProductionProgress(NOT_INITIALIZED_INT)
{

}

GameUnitProduction::GameUnitProduction(const GameUnitProduction& rhs)
{
	GameCityId = rhs.GameCityId;
	GameUnitId = rhs.GameUnitId;
	ProductionProgress = rhs.ProductionProgress;
}

int GameUnitProduction::GetGameCityId() const
{
	return GameCityId;
}

void GameUnitProduction::SetGameUnitId(int gameUnitId) const
{
	if (GameUnitId != gameUnitId)
	{
		ClearProductionProgress();
	}
	GameUnitId = gameUnitId;
}

int GameUnitProduction::GetGameUnitId() const
{
	return GameUnitId;
}

void GameUnitProduction::UpdateProductionProgress(int updateValue) const
{
	ProductionProgress += updateValue;
}

void GameUnitProduction::ClearProductionProgress() const
{
	ProductionProgress = 0;
}

int GameUnitProduction::GetProductionProgress() const
{
	return ProductionProgress;
}

void GameUnitProduction::SetProductionProgress(int progress) const
{
	ProductionProgress = progress;
}

bool GameUnitProduction::IsGameUnitInProduction() const
{
	return GameUnitId != NOT_INITIALIZED_INT;
}

QString GameUnitProduction::toString() const
{
	QString toString;
	toString += "GameCityId: ";
	toString += QString::number(GameCityId);
	toString += " GameUnitId: ";
	toString += QString::number(GameUnitId);
	return toString;
}
