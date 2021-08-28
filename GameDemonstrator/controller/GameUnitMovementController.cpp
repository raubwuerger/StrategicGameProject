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

bool GameUnitMovementController::CanUnitMove(int sourceGameUnitItemId, const MapHexItem* destination) const
{
	Q_ASSERT(destination);
	const GameUnitItem* gameUnitItem = GameUnitItemRepository::GetInstance()->GetGameUnitItemById(sourceGameUnitItemId);
	Q_ASSERT(gameUnitItem);

	GameCityItem* gameCityItem = GameCityItemRepository::GetInstance()->GetCityItemByGameMapItemId(destination->GetGameMapItemId());
	if (true == IsEnemyOnDestinationMapTile(destination->GetGameMapItemId()))
	{
		if (true == GameUnitAttackController::IsAttackSuccessful(gameUnitItem, GetEnemyGameUnit(destination->GetGameMapItemId())))
		{
			GameUnitItem* gameUnitItem = GameUnitItemRepository::GetInstance()->RemoveGameUnitItemByGameMapItemId(destination->GetGameMapItemId());
			Q_ASSERT(gameUnitItem);
			MapUnitItemRepository::GetInstance()->Remove(gameUnitItem->GetId());
		}
		else
		{
			if (false == GameUnitAttackController::IsUnitAttackable(gameUnitItem, GetEnemyGameUnit(destination->GetGameMapItemId())))
			{
				return false;
			}
			//TODO: Delete attcking Unit
			MapUnitItemRepository::GetInstance()->Remove(sourceGameUnitItemId);
			return false;
		}

		if (true == IsCityOnDestinationMapTile(destination->GetGameMapItemId()))
		{
			if (nullptr == gameCityItem)
			{
				Q_ASSERT(nullptr);
				return false;
			}
			
			if (nullptr != gameCityItem)
			{ 
				if (false == TerrainAccessTester::Accessable(gameUnitItem, destination))
				{
					return false;
				}
			}
		}
		else
		{
			return TerrainAccessTester::Accessable(gameUnitItem, destination);
		}
	}

	if (true == IsCityOnDestinationMapTile(destination->GetGameMapItemId()))
	{
		if (false == IsStackLimitSufficient(destination->GetGameMapItemId()))
		{
			return false;
		}
		if (false == TerrainAccessTester::Accessable(gameUnitItem, destination))
		{
			return false;
		}
		return AttackCity(gameUnitItem, GameCityItemRepository::GetInstance()->GetCityItemByGameMapItemId(destination->GetGameMapItemId()));
	}
	else
	{
		if (false == TerrainAccessTester::Accessable(gameUnitItem, destination))
		{
			return false;
		}
		if (false == IsStackLimitSufficient(destination->GetGameMapItemId()))
		{
			return false;
		}
		return true;
	}
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

bool GameUnitMovementController::IsEnemyOnDestinationMapTile(int gameMapItemId) const
{
	const GameUnitItem* gameUnitItem = GameUnitItemRepository::GetInstance()->GetGameUnitItemByGameMapItemId(gameMapItemId);
	if (nullptr == gameUnitItem)
	{
		return false;
	}
	return gameUnitItem->GetModelOwnerType() != CurrentMapTileOwner;
}

bool GameUnitMovementController::IsCityOnDestinationMapTile(int gameMapItemId) const
{
	return GameCityItemRepository::GetInstance()->IsCityOnGameMapItemId(gameMapItemId);
}

const GameUnitItem* GameUnitMovementController::GetEnemyGameUnit(int gameMapItemId) const
{
	return GameUnitItemRepository::GetInstance()->GetGameUnitItemByGameMapItemId(gameMapItemId);
}

bool GameUnitMovementController::IsStackLimitSufficient(int gameMapItemId) const
{
	int countGameUnitItems = GameUnitItemRepository::GetInstance()->GetGameUnitItemsCountByGameMapItemId(gameMapItemId);
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

	if (false == GameUnitAttackController::IsAttackSuccessful(gameUnitItem, gameCityItem))
	{
		return false;
	}

	if (gameUnitItem->GetModelOwnerTypeId() != gameCityItem->GetModelOwnerTypeId())
	{
		GameCityItemRepository::GetInstance()->ChangeOwner(gameCityItem, gameUnitItem->GetModelOwnerType());
	}

	return MapCityItemRepository::GetInstance()->UpdateMapCityItemOwner(gameCityItem);
}

