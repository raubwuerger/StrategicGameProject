#include "stdafx.h"
#include "GameUnitProductionController.h"
#include "LogInterface.h"
#include "GameUnitProduction.h"
#include "GameUnit.h"
#include "GameUnitFactory.h"
#include "GameUnitRepository.h"
#include "GameCityRepository.h"
#include "GameCity.h"
#include "Map\MapUnitItemFactory.h"
#include "command\CommandPlaceGameUnitOnMap.h"
#include "Model\ModelUnitTypeRepository.h"
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
	toUpdate->SetModelTypeId(gameUnitProduction.GetModelTypeId());
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
	gameUnitProduction->SetModelTypeId(MODEL_UNIT_ID_EFFICIENCY);
	gameUnitProduction->SetProductionProgress(0);

	CityProductions.insert(cityId, gameUnitProduction);

	return gameUnitProduction;
}

void GameUnitProductionController::RemoveGameUnitProduction(int cityId)
{
	CityProductions.remove(cityId);
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
	if (true == IsCityNeutral(gameUnitProduction))
	{
		return;
	}

	const ModelUnitType* modelUnitType = ModelUnitTypeRepository::GetInstance()->GetById(gameUnitProduction->GetModelTypeId());
	if (nullptr == modelUnitType)
	{
		Q_ASSERT(nullptr);
		return;
	}

	int unitProductionCost = modelUnitType->GetProductionCost();
	if (gameUnitProduction->GetProductionProgress() < unitProductionCost)
	{
		return;
	}

	const GameCity* gameCity = GameCityRepository::GetInstance()->GetById(gameUnitProduction->GetGameCityId());

	if (true == IsGameUnitOnMapTile(gameCity->GetGameMapTileId()))
	{
		return;
	}

	GameUnitParameterObject gameUnitParameterObject;
	gameUnitParameterObject.ModelUnitTypeObject = modelUnitType;
	gameUnitParameterObject.GameMapTileObject = gameCity->GetGameMapTile();
	gameUnitParameterObject.GameOwnerObject = gameCity->GetGameOwner();

	GameUnitFactory gameUnitFactory;
	const GameUnit* produced = gameUnitFactory.Create(gameUnitParameterObject);
	if (nullptr == produced)
	{
		return;
	}

	if (false == CommandPlaceGameUnitOnMap::PlaceGameUnit(produced, gameCity->GetGameMapTile()))
	{
		//TODO: Logausgabe
	}
	gameUnitProduction->ClearProductionProgress();
}

bool GameUnitProductionController::IsGameUnitOnMapTile(int gameMapId) const
{
	return nullptr != GameUnitRepository::GetInstance()->GetFirstGameUnitByGameMapTileId(gameMapId);
}

bool GameUnitProductionController::IsCityNeutral(const GameUnitProduction* gameUnitProduction) const
{
	const int CITY_OWNER_NEUTRAL = 1;
	GameCity* gameCity = GameCityRepository::GetInstance()->GetById(gameUnitProduction->GetGameCityId());
	Q_ASSERT(gameCity);
	return gameCity->GetGameOwnerId() == CITY_OWNER_NEUTRAL;
}
