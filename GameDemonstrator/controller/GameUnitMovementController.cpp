#include "stdafx.h"
#include "GameUnitMovementController.h"
#include "map/MapHexItemRepository.h"
#include "map/MapUnitItem.h"
#include "map/MapHexItem.h"
#include "game/GameMapItemRepository.h"
#include "game/GameMapItem.h"
#include "game/GameUnitItemRepository.h"
#include "game/GameUnitItem.h"
#include "model/ModelTerrainType.h"
#include "model/ModelUnitType.h"
#include "game/GameUnitItemRepository.h"
#include "controller/TerrainAccessTester.h"
#include "LogInterface.h"
#include "controller/GameUnitAttackController.h"
#include "map/MapUnitItemRepository.h"
#include "game/GameCityItemRepository.h"
#include "game/GameCityItem.h"
#include "map/MapCityItemRepository.h"

GameUnitMovementController::GameUnitMovementController(const GameUnitItem *activeGameUnitItem)
	: ActiveGameUnitItem(activeGameUnitItem),
	CurrentMapTileOwner(nullptr)
{
	Q_ASSERT(nullptr != ActiveGameUnitItem);
	CurrentMapTileOwner = GetCurrentMapTileOwner();
}

bool GameUnitMovementController::CanUnitMoveToDestination(int sourceGameUnitItemId, const MapHexItem* destination) const
{
	Q_ASSERT(destination);
	GameUnitItem* playerUnit = GameUnitItemRepository::GetInstance()->GetGameUnitItemById(sourceGameUnitItemId);
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
		const GameUnitItem* enemyUnit = GetEnemyGameUnit(destination->GetGameMapItemId());
		if (true == GameUnitAttackController::AttackUnit(playerUnit,enemyUnit))
		{
			enemyUnit = GameUnitItemRepository::GetInstance()->RemoveGameUnitItem(enemyUnit);
			Q_ASSERT(enemyUnit);
			playerUnit->Move();
			delete MapUnitItemRepository::GetInstance()->Remove(enemyUnit->GetId());
			if (true == IsEnemyCityOnDestinationMapTile(destination->GetGameMapItemId()) && true == GameUnitAttackController::IsCityOccupiable(playerUnit))
			{
				return false;
			}
			return true;
		}
		else
		{
			playerUnit = GameUnitItemRepository::GetInstance()->RemoveGameUnitItem(playerUnit);
			playerUnit->Move();
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
		GameCityItem* gameCityItem = GameCityItemRepository::GetInstance()->GetCityItemByGameMapItemId(destination->GetGameMapItemId());
		if (true == GameUnitAttackController::AttackCity(playerUnit, GameCityItemRepository::GetInstance()->GetCityItemByGameMapItemId(destination->GetGameMapItemId())))
		{
			GameCityItemRepository::GetInstance()->ChangeOwner(gameCityItem, playerUnit->GetModelOwnerType());
			MapCityItemRepository::GetInstance()->UpdateMapCityItemOwner(gameCityItem);
			playerUnit->Move();
			return true;
		}
		else
		{
			playerUnit->Move();
			playerUnit = GameUnitItemRepository::GetInstance()->RemoveGameUnitItem(playerUnit);
			delete MapUnitItemRepository::GetInstance()->Remove(playerUnit->GetId());
			return false;
		}
	}

	return true;
}

const ModelTerrainType* GameUnitMovementController::GetModelTerrainType(const MapUnitItem* mapUnitItem) const
{
	const MapHexItem* sourceMapHexItem = MapHexItemRepository::GetInstance()->GetMapHexItemById(mapUnitItem->GetMapHexItemId());
	if (nullptr == sourceMapHexItem)
	{
		return false;
	}

	GameMapItem* gameMapItem = GameMapItemRepository::GetInstance()->GetGameMapItemById(sourceMapHexItem->GetGameMapItemId());
	if (nullptr == gameMapItem)
	{
		return false;
	}

	return gameMapItem->GetTerrainType();
}

const GameUnitItem* GameUnitMovementController::GetGameUnitItem(const MapUnitItem* mapUnitItem) const
{
	const MapHexItem* sourceMapHexItem = MapHexItemRepository::GetInstance()->GetMapHexItemById(mapUnitItem->GetMapHexItemId());
	if (nullptr == sourceMapHexItem)
	{
		return false;
	}

	GameMapItem* gameMapItem = GameMapItemRepository::GetInstance()->GetGameMapItemById(sourceMapHexItem->GetGameMapItemId());
	if (nullptr == gameMapItem)
	{
		return false;
	}

	const ModelTerrainType* modelTerrainType = gameMapItem->GetTerrainType();
	if (nullptr == modelTerrainType)
	{
		return false;
	}

	return GameUnitItemRepository::GetInstance()->GetGameUnitItemById(mapUnitItem->GetGameUnitId());
}

bool GameUnitMovementController::IsOwnUnitOnDestinationMapTile(int gameMapItemId) const
{
	const GameUnitItem* gameUnitItem = GameUnitItemRepository::GetInstance()->GetGameUnitItemByGameMapItemId(gameMapItemId);
	if (nullptr == gameUnitItem)
	{
		return false;
	}
	return gameUnitItem->GetModelOwnerType() == CurrentMapTileOwner;
}

bool GameUnitMovementController::IsEnemyOnDestinationMapTile(int gameMapItemId) const
{
	const GameUnitItem* gameUnitItem = GameUnitItemRepository::GetInstance()->GetGameUnitItemByGameMapItemId(gameMapItemId);
	if (nullptr == gameUnitItem)
	{
		return false;
	}
	return gameUnitItem->GetModelOwnerType() != CurrentMapTileOwner;
}

bool GameUnitMovementController::IsEnemyCityOnDestinationMapTile(int gameMapItemId) const
{
	GameCityItem* gameCityItem = GameCityItemRepository::GetInstance()->GetCityItemByGameMapItemId(gameMapItemId);
	if (nullptr == gameCityItem)
	{
		return false;
	}
	int ownOwnerTypeId = ActiveGameUnitItem->GetModelOwnerTypeId();
	int enemyOwnerTypeId = gameCityItem->GetModelOwnerTypeId();
	return ownOwnerTypeId != enemyOwnerTypeId;
}

const GameUnitItem* GameUnitMovementController::GetEnemyGameUnit(int gameMapItemId) const
{
	return GameUnitItemRepository::GetInstance()->GetGameUnitItemByGameMapItemId(gameMapItemId);
}

bool GameUnitMovementController::IsStackLimitSufficient(int gameMapItemId) const
{
	int countGameUnitItems = GameUnitItemRepository::GetInstance()->IsGameUnitItemOnGameMapItem(gameMapItemId);
	const int MAX_STACK_SIZE = 1;
	bool isStackLimitSufficient = countGameUnitItems < MAX_STACK_SIZE;
	if (false == isStackLimitSufficient )
	{
		jha::GetLog()->Log_DEBUG(QObject::tr("Stack limit exceeded on game map item id %1").arg(QString::number(gameMapItemId)));
	}
	return isStackLimitSufficient;
}

const ModelOwnerType* GameUnitMovementController::GetCurrentMapTileOwner()
{
	if (nullptr == ActiveGameUnitItem)
	{
		Q_ASSERT(nullptr); // Something went wrong
		return nullptr;
	}

	return ActiveGameUnitItem->GetModelOwnerType();
}

bool GameUnitMovementController::AttackCity(const GameUnitItem* gameUnitItem, const GameCityItem* gameCityItem) const
{
	if (false == GameUnitAttackController::IsCityOccupiable(gameUnitItem))
	{
		return false;
	}

	if (false == GameUnitAttackController::AttackCity(gameUnitItem, gameCityItem))
	{
		return false;
	}

	if (gameUnitItem->GetModelOwnerTypeId() != gameCityItem->GetModelOwnerTypeId())
	{
		GameCityItemRepository::GetInstance()->ChangeOwner(gameCityItem, gameUnitItem->GetModelOwnerType());
	}

	return MapCityItemRepository::GetInstance()->UpdateMapCityItemOwner(gameCityItem);
}

