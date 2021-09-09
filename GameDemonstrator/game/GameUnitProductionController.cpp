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
#include "Map\MapUnitItemFactory.h"
#include "command\CommandPlaceGameUnitOnMap.h"

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

	return true;
}

bool GameUnitProductionController::UpdateGameUnitProduction(const GameUnitProduction& gameUnitProduction)
{
	Q_ASSERT(&gameUnitProduction);

	if (false == CityProductions.contains(gameUnitProduction.GetGameCityId()))
	{
		jha::GetLog()->Log_DEBUG(QObject::tr("GameUnitProduction not registered! %1").arg(gameUnitProduction.toString()));
		return false;
	}
	
	const GameUnitProduction* toUpdate = CityProductions[gameUnitProduction.GetGameCityId()];
	toUpdate->SetGameUnitId(gameUnitProduction.GetGameUnitId());
	toUpdate->SetProductionProgress(gameUnitProduction.GetProductionProgress());
	return true;
}

const GameUnitProduction* GameUnitProductionController::CreateDefaultGameUnitProduction(int cityId)
{
	if (cityId <= 0)
	{
		jha::GetLog()->Log_DEBUG(QObject::tr("GameUnitProduction not allowed for city id <=0!"));
		return nullptr;
	}

	if (true == CityProductions.contains(cityId))
	{
		jha::GetLog()->Log_DEBUG(QObject::tr("GameUnitProduction city id=%1 alreads exists!").arg(QString::number(cityId)));
		return nullptr;
	}

	GameUnitProduction* gameUnitProduction = new GameUnitProduction(cityId);
	gameUnitProduction->SetGameUnitId(GAME_UNIT_ID_EFFICIENCY);
	gameUnitProduction->SetProductionProgress(0);

	CityProductions.insert(cityId, gameUnitProduction);

	return gameUnitProduction;
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

	if (true == IsGameUnitOnMapItem(gameCityItem->GetGameMapItemId()))
	{
		return;
	}

	GameUnitParameterObject gameUnitParameterObject;
	gameUnitParameterObject.ModelUnitTypeObject = gameUnitItem->GetModelUnitType();
	gameUnitParameterObject.GameMapItemObject = gameCityItem->GetGameMapItem();
	gameUnitParameterObject.GameOwnerItemObject = gameCityItem->GetGameOwnerItem();

	GameUnitItemFactory gameUnitItemFactory;
	const GameUnitItem* produced = gameUnitItemFactory.CreateGameUnitItem(gameUnitParameterObject);
	if (nullptr == produced)
	{
		return;
	}

	if (false == CommandPlaceGameUnitOnMap::PlaceGameUnit(produced, gameCityItem->GetGameMapItem()))
	{
		//TODO: Logausgabe
	}
	gameUnitProduction->ClearProductionProgress();
}

bool GameUnitProductionController::IsGameUnitOnMapItem(int gameMapId) const
{
	return nullptr != GameUnitItemRepository::GetInstance()->GetGameUnitItemByGameMapItemId(gameMapId);
}
