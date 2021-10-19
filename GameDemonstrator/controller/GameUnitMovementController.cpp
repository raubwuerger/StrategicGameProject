#include "stdafx.h"
#include "model/ModelTerrainType.h"
#include "model/ModelUnitType.h"
#include "GameUnitMovementController.h"
#include "game/GameMapTileRepository.h"
#include "game/GameMapTile.h"
#include "game/GameUnit.h"
#include "game/GameUnitRepository.h"
#include "game/GameUnitFactory.h"
#include "game/GameCityRepository.h"
#include "game/GameCity.h"
#include "game/GameConfig.h"
#include "map/MapHexItemRepository.h"
#include "map/MapUnitItem.h"
#include "map/MapHexItem.h"
#include "map/MapUnitItemRepository.h"
#include "map/MapCityItemRepository.h"
#include "map/MapUnitItemFactory.h"
#include "TerrainAccessTester.h"
#include "GameUnitAttackController.h"
#include "GameUnitTransportController.h"
#include "GameUnitHelper.h"
#include "LogInterface.h"

GameUnitMovementController::GameUnitMovementController( GameUnit *activeGameUnitItem)
	: ActiveGameUnitItem(activeGameUnitItem)
{
	Q_ASSERT(ActiveGameUnitItem);
}

bool GameUnitMovementController::Move( const MapHexItem* destMapHexItem)
{
	if (false == CanUnitMove(ActiveGameUnitItem->GetId(), destMapHexItem))
	{
		return false;
	}

	const MapHexItem*  sourceMapHexItem = MapHexItemRepository::GetInstance()->GetById(GameUnitHelper::GetMapHexItemId(ActiveGameUnitItem));
	Q_ASSERT(sourceMapHexItem);

	MapUnitItem *mapUnitItem = MapUnitItemRepository::GetInstance()->GetById(ActiveGameUnitItem->GetId());
	Q_ASSERT(mapUnitItem);
	mapUnitItem->SetMapHexItemId(destMapHexItem->GetId());
	mapUnitItem->SetMapHexItemId(destMapHexItem->GetId());
	mapUnitItem->setPos(destMapHexItem->GetTopLeftPoint() - MapUnitItemFactory::MAPHEXITEM_OFFSET);

	GameUnitFactory gameUnitItemFactory;
	GameUnit* movedGameUnitItem = gameUnitItemFactory.Update(CreateUpdateGameUnit(destMapHexItem));
	GameUnitRepository::GetInstance()->UpdateGameUnitOnGameMapTile(movedGameUnitItem, sourceMapHexItem->GetId());
	return movedGameUnitItem->Move();
}

GameUnitParameterObject GameUnitMovementController::CreateUpdateGameUnit(const MapHexItem* destMapHexItem)
{
	GameUnitParameterObject gameUnitParameterObject;
	gameUnitParameterObject.GameUnitObject = ActiveGameUnitItem;
	gameUnitParameterObject.GameOwnerObject = ActiveGameUnitItem->GetGameOwner();
	gameUnitParameterObject.GameMapTileId = destMapHexItem->GetId();
	gameUnitParameterObject.ModelUnitTypeObject = ActiveGameUnitItem->GetModelUnitType();
	return gameUnitParameterObject;
}

bool GameUnitMovementController::CanUnitMove(int sourceGameUnitItemId, const MapHexItem* destination)
{
	Q_ASSERT(destination);
	if (ActiveGameUnitItem->GetModelOwnerTypeId() != GameConfig::PlayerId)
	{
		return false;
	}
	if (false == ActiveGameUnitItem->CanMove())
	{
		return false;
	}

	GameUnitTransportController gameUnitTransportController(ActiveGameUnitItem);
	if (true == gameUnitTransportController.EmbarkUnit(destination))
	{
		return true;
	}

	if (true == gameUnitTransportController.DisembarkUnit(destination))
	{
		return true;
	}

	if (true == GameUnitHelper::IsOwnUnitOnDestinationMapTile(ActiveGameUnitItem, destination->GetId()))
	{
		return false;
	}

	if (false == TerrainAccessTester::Accessable(ActiveGameUnitItem, destination))
	{
		return false;
	}

	if (true == GameUnitHelper::IsEnemyOnDestinationMapTile(ActiveGameUnitItem, destination->GetId()))
	{
		const GameUnit* enemyUnit = GameUnitHelper::GetEnemyGameUnit(destination->GetId());
		if (true == GameUnitAttackController::AttackUnit(ActiveGameUnitItem, enemyUnit))
		{
			enemyUnit = GameUnitRepository::GetInstance()->RemoveGameUnit(enemyUnit);
			Q_ASSERT(enemyUnit);
			ActiveGameUnitItem->Move();
			EmitMapUnitItemMoved(ActiveGameUnitItem);
			delete MapUnitItemRepository::GetInstance()->Remove(enemyUnit->GetId());
			if (true == IsEnemyCityOnDestinationMapTile(destination->GetId()) && true == GameUnitAttackController::IsCityOccupiable(ActiveGameUnitItem))
			{
				return false;
			}
			return true;
		}
		else
		{
			ActiveGameUnitItem = GameUnitRepository::GetInstance()->RemoveGameUnit(ActiveGameUnitItem);
			ActiveGameUnitItem->Move();
			EmitMapUnitItemMoved(ActiveGameUnitItem);
			delete MapUnitItemRepository::GetInstance()->Remove(ActiveGameUnitItem->GetId());
			return false;
		}
	}

	if (true == IsEnemyCityOnDestinationMapTile(destination->GetId()))
	{
		if (false == GameUnitAttackController::IsCityOccupiable(ActiveGameUnitItem))
		{
			return true;
		}
		GameCity* gameCityItem = GameCityRepository::GetInstance()->GetGameCityByGameMapTileId(destination->GetId());
		if (true == GameUnitAttackController::AttackCity(ActiveGameUnitItem, GameCityRepository::GetInstance()->GetGameCityByGameMapTileId(destination->GetId())))
		{
			GameCityRepository::GetInstance()->ChangeOwner(gameCityItem, ActiveGameUnitItem->GetGameOwner());
			MapCityItemRepository::GetInstance()->UpdateMapCityItemOwner(gameCityItem);
			ActiveGameUnitItem->Move();
			EmitMapUnitItemMoved(ActiveGameUnitItem);
			return true;
		}
		else
		{
			ActiveGameUnitItem->Move();
			EmitMapUnitItemMoved(ActiveGameUnitItem);
			ActiveGameUnitItem = GameUnitRepository::GetInstance()->RemoveGameUnit(ActiveGameUnitItem);
			delete MapUnitItemRepository::GetInstance()->Remove(ActiveGameUnitItem->GetId());
			return false;
		}
	}

	EmitMapUnitItemMoved(ActiveGameUnitItem);
	return true;

}

bool GameUnitMovementController::IsEnemyCityOnDestinationMapTile(int gameMapItemId) const
{
	GameCity* gameCityItem = GameCityRepository::GetInstance()->GetGameCityByGameMapTileId(gameMapItemId);
	if (nullptr == gameCityItem)
	{
		return false;
	}
	int ownOwnerTypeId = ActiveGameUnitItem->GetModelOwnerTypeId();
	int enemyOwnerTypeId = gameCityItem->GetGameOwnerId();
	return ownOwnerTypeId != enemyOwnerTypeId;
}

bool GameUnitMovementController::AttackCity(const GameUnit* gameUnitItem, const GameCity* gameCityItem) const
{
	if (false == GameUnitAttackController::IsCityOccupiable(gameUnitItem))
	{
		return false;
	}

	if (false == GameUnitAttackController::AttackCity(gameUnitItem, gameCityItem))
	{
		return false;
	}

	if (gameUnitItem->GetModelOwnerTypeId() != gameCityItem->GetGameOwnerId())
	{
		GameCityRepository::GetInstance()->ChangeOwner(gameCityItem, gameUnitItem->GetGameOwner());
	}

	return MapCityItemRepository::GetInstance()->UpdateMapCityItemOwner(gameCityItem);
}

bool GameUnitMovementController::EmitMapUnitItemMoved(const GameUnit* gameUnitItem) const
{
	MapUnitItem* mapUnitItem = MapUnitItemRepository::GetInstance()->GetById(gameUnitItem->GetId());
	if (nullptr == mapUnitItem)
	{
		return false;
	}
	mapUnitItem->EmitSignalUnitItemEntered();
	return true;
}

