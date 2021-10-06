#include "stdafx.h"
#include "GameUnitProduction.h"

GameUnitProduction::GameUnitProduction(int gameCityId) 
	: GameCityId(gameCityId),
	ModelUnitTypeId(NOT_INITIALIZED_INT),
	ProductionProgress(NOT_INITIALIZED_INT)
{

}

GameUnitProduction::GameUnitProduction(const GameUnitProduction& rhs)
{
	GameCityId = rhs.GameCityId;
	ModelUnitTypeId = rhs.ModelUnitTypeId;
	ProductionProgress = rhs.ProductionProgress;
}

int GameUnitProduction::GetGameCityId() const
{
	return GameCityId;
}

void GameUnitProduction::SetModelTypeId(int modelTypeId) const
{
	if (ModelUnitTypeId != modelTypeId)
	{
		ClearProductionProgress();
	}
	ModelUnitTypeId = modelTypeId;
}

int GameUnitProduction::GetModelTypeId() const
{
	return ModelUnitTypeId;
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
	return ModelUnitTypeId != NOT_INITIALIZED_INT;
}

QString GameUnitProduction::toString() const
{
	QString toString;
	toString += "GameCityId: ";
	toString += QString::number(GameCityId);
	toString += " GameUnitId: ";
	toString += QString::number(ModelUnitTypeId);
	return toString;
}
