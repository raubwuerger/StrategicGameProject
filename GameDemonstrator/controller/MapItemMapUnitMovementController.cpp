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

bool MapItemMapUnitMovementController::CanUnitMove(const MapUnitItem* mapUnitItem)
{
	MapHexItem* sourceMapHexItem = MapHexItemRepository::GetInstance()->GetMapHexItemById(mapUnitItem->GetMapHexItemId());
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

	const GameUnitItem* gameUnitItem = GameUnitItemRepository::GetInstance()->GetGameUnitItemById(mapUnitItem->GetGameUnitId());
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

bool MapItemMapUnitMovementController::CanUnitMove(const MapHexItem* mapHexItem, const GameUnitItem* gameUnitItem)
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

bool MapItemMapUnitMovementController::CanUnitMove(const ModelUnitType* modelUnitType, const int gameMapItemId)
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
