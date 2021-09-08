#include "stdafx.h"
#include "GameUnitProductionRepository.h"
#include "LogInterface.h"
#include "GameUnitProduction.h"
#include "GameUnitItem.h"
#include "GameUnitItemFactory.h"
#include "GameUnitItemRepository.h"
#include "GameCityItemRepository.h"
#include "GameCityItem.h"
#include "Model\ModelUnitType.h"

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

bool GameUnitProductionRepository::RegisterGameUnitProduction(const GameUnitProduction* gameUnitProduction)
{
	Q_ASSERT(gameUnitProduction);
	if (nullptr == gameUnitProduction)
	{
		return false;
	}

	CityProductions.insert(gameUnitProduction->GetGameCityId(), gameUnitProduction);

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

void GameUnitProductionRepository::UpdateTurn()
{
	QMapIterator<int, const GameUnitProduction*> iterator(CityProductions);
	while (iterator.hasNext())
	{
		CreateGameUnit(iterator.next().value());
	}
}

GameUnitProductionRepository::GameUnitProductionRepository()
{

}

void GameUnitProductionRepository::CreateGameUnit( const GameUnitProduction* gameUnitProduction )
{
	const GameUnitItem* gameUnitItem = GameUnitItemRepository::GetInstance()->GetGameUnitItemById(gameUnitProduction->GetGameCityId());
	if (nullptr == gameUnitItem)
	{
		Q_ASSERT(nullptr);
		return;
	}

	int unitProductionCost = gameUnitItem->GetModelUnitType()->GetProductionCost();
	if (gameUnitProduction->GetProductionProgress() < unitProductionCost)
	{
		return;
	}

	const GameCityItem* gameCityItem = GameCityItemRepository::GetInstance()->GetGameCityItemById(gameUnitProduction->GetGameCityId());

	GameUnitParameterObject gameUnitParameterObject;
	gameUnitParameterObject.ModelUnitTypeObject = gameUnitItem->GetModelUnitType();
	gameUnitParameterObject.GameMapItemObject = gameCityItem->GetGameMapItem();
	gameUnitParameterObject.GameOwnerItemObject = gameCityItem->GetGameOwnerItem();

	GameUnitItemFactory gameUnitItemFactory;
	const GameUnitItem* produced = gameUnitItemFactory.CreateGameUnitItem(gameUnitParameterObject);
	
}
