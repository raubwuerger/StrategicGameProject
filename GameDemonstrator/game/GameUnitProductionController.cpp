#include "stdafx.h"
#include "GameUnitProductionController.h"
#include "LogInterface.h"
#include "GameUnitProduction.h"
#include "GameUnitItem.h"
#include "GameUnitItemFactory.h"
#include "GameUnitItemRepository.h"
#include "GameCityItemRepository.h"
#include "GameCityItem.h"
#include "Model\ModelUnitType.h"

GameUnitProductionController* GameUnitProductionController::Instance = nullptr;

GameUnitProductionController* GameUnitProductionController::GetInstance()
{
	if ( nullptr != Instance )
	{
		return Instance;
	}

	Instance = new GameUnitProductionController();
	return Instance;
}

bool GameUnitProductionController::RegisterGameUnitProduction(const GameUnitProduction* gameUnitProduction)
{
	Q_ASSERT(gameUnitProduction);
	if (nullptr == gameUnitProduction)
	{
		return false;
	}

	CityProductions.insert(gameUnitProduction->GetGameCityId(), gameUnitProduction);

	return false;
}

bool GameUnitProductionController::Init()
{
	return true;
}

void GameUnitProductionController::Release()
{
	delete Instance;
	Instance = nullptr;
}

void GameUnitProductionController::UpdateTurn()
{
	QMapIterator<int, const GameUnitProduction*> iterator(CityProductions);
	while (iterator.hasNext())
	{
		CreateGameUnit(iterator.next().value());
	}
}

GameUnitProductionController::GameUnitProductionController()
{

}

void GameUnitProductionController::CreateGameUnit( const GameUnitProduction* gameUnitProduction )
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
