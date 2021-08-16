#include "stdafx.h"
#include "MapItemMapUnitMovementController.h"
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

MapItemMapUnitMovementController::MapItemMapUnitMovementController(const MapHexItem *mapHexItem)
	: Destination(mapHexItem)
{
	Q_ASSERT(nullptr != Destination);
}

bool MapItemMapUnitMovementController::CanUnitMove(const MapUnitItem* mapUnitItem) const
{
	const GameUnitItem* gameUnitItem = GetGameUnitItem(mapUnitItem);
	if (false == IsTerrainTypeAccessible(mapUnitItem, gameUnitItem))
	{
		return false;
	}
	return IsStackLimitSufficient(Destination->GetGameMapItemId());
}

bool MapItemMapUnitMovementController::IsTerrainTypeAccessible(const MapUnitItem* mapUnitItem, const GameUnitItem* gameUnitItem) const
{
	const ModelTerrainType* modelTerrainType = GetModelTerrainType(mapUnitItem);
	if (nullptr == modelTerrainType)
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

	return modelUnitType->IsTerrainTypeValid(modelTerrainType->GetId());
}

bool MapItemMapUnitMovementController::CanUnitMove(const MapHexItem* mapHexItem, int gameUnitItemId) const
{
	const GameUnitItem* gameUnitItem = GameUnitItemRepository::GetInstance()->GetGameUnitItemById(gameUnitItemId);
	if (false == IsTerrainTypeAccessible(mapHexItem, gameUnitItem))
	{
		return false;
	}
	return IsStackLimitSufficient(Destination->GetGameMapItemId());
}

bool MapItemMapUnitMovementController::IsTerrainTypeAccessible(const MapHexItem* mapHexItem, const GameUnitItem* gameUnitItem) const
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

bool MapItemMapUnitMovementController::CanUnitMove(const ModelUnitType* modelUnitType, const int gameMapItemId) const
{
	if (false == IsTerrainTypeAccessible(modelUnitType, gameMapItemId))
	{
		return false;
	}

	return IsStackLimitSufficient(gameMapItemId);
}

const ModelTerrainType* MapItemMapUnitMovementController::GetModelTerrainType(const MapUnitItem* mapUnitItem) const
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

const GameUnitItem* MapItemMapUnitMovementController::GetGameUnitItem(const MapUnitItem* mapUnitItem) const
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

bool MapItemMapUnitMovementController::IsTerrainTypeAccessible(const ModelUnitType* modelUnitType, const int gameMapItemId) const
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

bool MapItemMapUnitMovementController::IsStackLimitSufficient(int gameMapItemId) const
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

