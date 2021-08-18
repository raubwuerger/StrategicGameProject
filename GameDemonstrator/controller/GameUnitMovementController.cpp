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
#include "LogInterface.h"

GameUnitMovementController::GameUnitMovementController(const MapHexItem *mapHexItem)
	: Destination(mapHexItem)
{
	Q_ASSERT(nullptr != Destination);
}

bool GameUnitMovementController::CanUnitMove(int gameUnitItemId, const MapHexItem* mapHexItem) const
{
	const GameUnitItem* gameUnitItem = GameUnitItemRepository::GetInstance()->GetGameUnitItemById(gameUnitItemId);
	if (false == IsTerrainTypeAccessible(mapHexItem, gameUnitItem))
	{
		return false;
	}
	return IsStackLimitSufficient(Destination->GetGameMapItemId());
}

bool GameUnitMovementController::IsTerrainTypeAccessible(const MapHexItem* mapHexItem, const GameUnitItem* gameUnitItem) const
{
	if (nullptr == mapHexItem)
	{
		return false;
	}

	if (nullptr == gameUnitItem)
	{
		return false;
	}

	const ModelUnitType* modelUnitType = gameUnitItem->GetModelUnitType();
	if (nullptr == modelUnitType)
	{
		return false;
	}

	const GameMapItem* gameMapItem = GameMapItemRepository::GetInstance()->GetGameMapItemById(mapHexItem->GetGameMapItemId());
	if (nullptr == gameMapItem)
	{
		return false;
	}

	const ModelTerrainType* modelTerrainType = gameMapItem->GetTerrainType();
	if (nullptr == modelTerrainType)
	{
		return false;
	}

	return modelUnitType->IsTerrainTypeValid(modelTerrainType->GetId());
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

bool GameUnitMovementController::IsTerrainTypeAccessible(const int gameMapItemId, const ModelUnitType* modelUnitType) const
{
	if (nullptr == modelUnitType)
	{
		return false;
	}

	GameMapItem* gameMapItem = GameMapItemRepository::GetInstance()->GetGameMapItemById(gameMapItemId);
	if (nullptr == gameMapItem)
	{
		return false;
	}

	const ModelTerrainType* modelTerrainType = gameMapItem->GetTerrainType();
	if (nullptr == modelTerrainType)
	{
		return false;
	}

	return modelUnitType->IsTerrainTypeValid(modelTerrainType->GetId());
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

