#include "stdafx.h"
#include "TerrainAccessTester.h"
#include "game/GameUnitItem.h"
#include "game/GameMapItem.h"
#include "game/GameMapItemRepository.h"
#include "map/MapHexItem.h"
#include "model/ModelTerrainType.h"
#include "model/ModelUnitType.h"

bool TerrainAccessTester::Accessable(const ModelUnitType* modelUnitType, const int gameMapItemId)
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

	return modelUnitType->IsTerrainTypeAccessible(modelTerrainType->GetId());
}

bool TerrainAccessTester::Accessable(const GameUnitItem* gameUnitItem, const MapHexItem* mapHexItem)
{
	if (nullptr == gameUnitItem)
	{
		return false;
	}

	if (nullptr == mapHexItem)
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

	return modelUnitType->IsTerrainTypeAccessible(modelTerrainType->GetId());
}

bool TerrainAccessTester::Accessable(const GameUnitItem* gameUnitItem, const ModelTerrainType* modelTerrainType)
{
	if (nullptr == gameUnitItem)
	{
		return false;
	}

	if (nullptr == modelTerrainType)
	{
		return false;
	}

	const ModelUnitType* modelUnitType = gameUnitItem->GetModelUnitType();
	if (nullptr == modelUnitType)
	{
		return false;
	}

	return modelUnitType->IsTerrainTypeAccessible(modelTerrainType->GetId());
}
