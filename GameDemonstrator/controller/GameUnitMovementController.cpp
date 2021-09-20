#include "stdafx.h"
#include "model/ModelTerrainType.h"
#include "model/ModelUnitType.h"
#include "GameUnitMovementController.h"
#include "game/GameMapTileRepository.h"
#include "game/GameMapTile.h"
#include "game/GameUnitRepository.h"
#include "game/GameUnit.h"
#include "game/GameUnitRepository.h"
#include "game/GameCityRepository.h"
#include "game/GameCity.h"
#include "map/MapHexItemRepository.h"
#include "map/MapUnitItem.h"
#include "map/MapHexItem.h"
#include "map/MapUnitItemRepository.h"
#include "map/MapCityItemRepository.h"
#include "controller/TerrainAccessTester.h"
#include "controller/GameUnitAttackController.h"
#include "LogInterface.h"

GameUnitMovementController::GameUnitMovementController(const GameUnit *activeGameUnitItem)
	: ActiveGameUnitItem(activeGameUnitItem),
	CurrentMapTileOwner(nullptr)
{
	Q_ASSERT(nullptr != ActiveGameUnitItem);
	CurrentMapTileOwner = GetCurrentMapTileOwner();
}

bool GameUnitMovementController::CanUnitMoveToDestination(int sourceGameUnitItemId, const MapHexItem* destination) const
{
	Q_ASSERT(destination);
	GameUnit* playerUnit = GameUnitRepository::GetInstance()->GetById(sourceGameUnitItemId);
	Q_ASSERT(playerUnit);
	if( false == playerUnit->CanMove() )
	{
		return false;
	}

	if (false == TerrainAccessTester::Accessable(playerUnit, destination))
	{
		return false;
	}

	if (true == IsOwnUnitOnDestinationMapTile(destination->GetGameMapItemId()))
	{
		return false;
	}

	if (true == IsEnemyOnDestinationMapTile(destination->GetGameMapItemId()))
	{
		const GameUnit* enemyUnit = GetEnemyGameUnit(destination->GetGameMapItemId());
		if (true == GameUnitAttackController::AttackUnit(playerUnit,enemyUnit))
		{
			enemyUnit = GameUnitRepository::GetInstance()->RemoveGameUnit(enemyUnit);
			Q_ASSERT(enemyUnit);
			playerUnit->Move();
			EmitMapUnitItemMoved(playerUnit);
			delete MapUnitItemRepository::GetInstance()->Remove(enemyUnit->GetId());
			if (true == IsEnemyCityOnDestinationMapTile(destination->GetGameMapItemId()) && true == GameUnitAttackController::IsCityOccupiable(playerUnit))
			{
				return false;
			}
			return true;
		}
		else
		{
			playerUnit = GameUnitRepository::GetInstance()->RemoveGameUnit(playerUnit);
			playerUnit->Move();
			EmitMapUnitItemMoved(playerUnit);
			delete MapUnitItemRepository::GetInstance()->Remove(playerUnit->GetId());
			return false;
		}
	}

	if (true == IsEnemyCityOnDestinationMapTile(destination->GetGameMapItemId()))
	{
		if (false == GameUnitAttackController::IsCityOccupiable(playerUnit) )
		{
			return true;
		}
		GameCity* gameCityItem = GameCityRepository::GetInstance()->GetGameCityByGameMapTileId(destination->GetGameMapItemId());
		if (true == GameUnitAttackController::AttackCity(playerUnit, GameCityRepository::GetInstance()->GetGameCityByGameMapTileId(destination->GetGameMapItemId())))
		{
			GameCityRepository::GetInstance()->ChangeOwner(gameCityItem, playerUnit->GetGameOwner());
			MapCityItemRepository::GetInstance()->UpdateMapCityItemOwner(gameCityItem);
			playerUnit->Move();
			EmitMapUnitItemMoved(playerUnit);
			return true;
		}
		else
		{
			playerUnit->Move();
			EmitMapUnitItemMoved(playerUnit);
			playerUnit = GameUnitRepository::GetInstance()->RemoveGameUnit(playerUnit);
			delete MapUnitItemRepository::GetInstance()->Remove(playerUnit->GetId());
			return false;
		}
	}

	EmitMapUnitItemMoved(playerUnit);
	return true;
}

bool GameUnitMovementController::IsOwnUnitOnDestinationMapTile(int gameMapItemId) const
{
	const GameUnit* gameUnitItem = GameUnitRepository::GetInstance()->GetByGameMapTileId(gameMapItemId);
	if (nullptr == gameUnitItem)
	{
		return false;
	}
	return gameUnitItem->GetGameOwner() == CurrentMapTileOwner;
}

bool GameUnitMovementController::IsEnemyOnDestinationMapTile(int gameMapItemId) const
{
	const GameUnit* gameUnitItem = GameUnitRepository::GetInstance()->GetByGameMapTileId(gameMapItemId);
	if (nullptr == gameUnitItem)
	{
		return false;
	}
	return gameUnitItem->GetGameOwner() != CurrentMapTileOwner;
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

const GameUnit* GameUnitMovementController::GetEnemyGameUnit(int gameMapItemId) const
{
	return GameUnitRepository::GetInstance()->GetByGameMapTileId(gameMapItemId);
}

const GameOwner* GameUnitMovementController::GetCurrentMapTileOwner()
{
	if (nullptr == ActiveGameUnitItem)
	{
		Q_ASSERT(nullptr); // Something went wrong
		return nullptr;
	}

	return ActiveGameUnitItem->GetGameOwner();
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

