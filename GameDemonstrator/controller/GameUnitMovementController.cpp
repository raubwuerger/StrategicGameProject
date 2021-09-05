#include "stdafx.h"
#include "model/ModelTerrainType.h"
#include "model/ModelUnitType.h"
#include "GameUnitMovementController.h"
#include "game/GameMapItemRepository.h"
#include "game/GameMapItem.h"
#include "game/GameUnitItemRepository.h"
#include "game/GameUnitItem.h"
#include "game/GameUnitItemRepository.h"
#include "game/GameCityItemRepository.h"
#include "game/GameCityItem.h"
#include "map/MapHexItemRepository.h"
#include "map/MapUnitItem.h"
#include "map/MapHexItem.h"
#include "map/MapUnitItemRepository.h"
#include "map/MapCityItemRepository.h"
#include "controller/TerrainAccessTester.h"
#include "controller/GameUnitAttackController.h"
#include "LogInterface.h"

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
			GameCityItemRepository::GetInstance()->ChangeOwner(gameCityItem, playerUnit->GetGameOwnerItem());
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

bool GameUnitMovementController::IsOwnUnitOnDestinationMapTile(int gameMapItemId) const
{
	const GameUnitItem* gameUnitItem = GameUnitItemRepository::GetInstance()->GetGameUnitItemByGameMapItemId(gameMapItemId);
	if (nullptr == gameUnitItem)
	{
		return false;
	}
	return gameUnitItem->GetGameOwnerItem() == CurrentMapTileOwner;
}

bool GameUnitMovementController::IsEnemyOnDestinationMapTile(int gameMapItemId) const
{
	const GameUnitItem* gameUnitItem = GameUnitItemRepository::GetInstance()->GetGameUnitItemByGameMapItemId(gameMapItemId);
	if (nullptr == gameUnitItem)
	{
		return false;
	}
	return gameUnitItem->GetGameOwnerItem() != CurrentMapTileOwner;
}

bool GameUnitMovementController::IsEnemyCityOnDestinationMapTile(int gameMapItemId) const
{
	GameCityItem* gameCityItem = GameCityItemRepository::GetInstance()->GetCityItemByGameMapItemId(gameMapItemId);
	if (nullptr == gameCityItem)
	{
		return false;
	}
	int ownOwnerTypeId = ActiveGameUnitItem->GetModelOwnerTypeId();
	int enemyOwnerTypeId = gameCityItem->GetGameOwnerItemId();
	return ownOwnerTypeId != enemyOwnerTypeId;
}

const GameUnitItem* GameUnitMovementController::GetEnemyGameUnit(int gameMapItemId) const
{
	return GameUnitItemRepository::GetInstance()->GetGameUnitItemByGameMapItemId(gameMapItemId);
}

const GameOwnerItem* GameUnitMovementController::GetCurrentMapTileOwner()
{
	if (nullptr == ActiveGameUnitItem)
	{
		Q_ASSERT(nullptr); // Something went wrong
		return nullptr;
	}

	return ActiveGameUnitItem->GetGameOwnerItem();
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

	if (gameUnitItem->GetModelOwnerTypeId() != gameCityItem->GetGameOwnerItemId())
	{
		GameCityItemRepository::GetInstance()->ChangeOwner(gameCityItem, gameUnitItem->GetGameOwnerItem());
	}

	return MapCityItemRepository::GetInstance()->UpdateMapCityItemOwner(gameCityItem);
}

