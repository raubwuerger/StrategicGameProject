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
	Q_ASSERT(modelUnitType);

	GameMapItem* gameMapItem = GameMapItemRepository::GetInstance()->GetGameMapItemById(gameMapItemId);
	Q_ASSERT(gameMapItem);

	const ModelTerrainType* modelTerrainType = gameMapItem->GetTerrainType();
	Q_ASSERT(modelTerrainType);

	return modelUnitType->IsTerrainTypeAccessible(modelTerrainType->GetId());
}

bool TerrainAccessTester::Accessable(const GameUnitItem* gameUnitItem, const MapHexItem* mapHexItem)
{
	Q_ASSERT(gameUnitItem);
	Q_ASSERT(mapHexItem);

	const ModelUnitType* modelUnitType = gameUnitItem->GetModelUnitType();
	Q_ASSERT(modelUnitType);

	const GameMapItem* gameMapItem = GameMapItemRepository::GetInstance()->GetGameMapItemById(mapHexItem->GetGameMapItemId());
	Q_ASSERT(gameMapItem);

	const ModelTerrainType* modelTerrainType = gameMapItem->GetTerrainType();
	Q_ASSERT(modelTerrainType);

	return modelUnitType->IsTerrainTypeAccessible(modelTerrainType->GetId());
}

bool TerrainAccessTester::Accessable(const GameUnitItem* gameUnitItem, const ModelTerrainType* modelTerrainType)
{
	Q_ASSERT(gameUnitItem);
	Q_ASSERT(modelTerrainType);

	const ModelUnitType* modelUnitType = gameUnitItem->GetModelUnitType();
	Q_ASSERT(modelUnitType);

	return modelUnitType->IsTerrainTypeAccessible(modelTerrainType->GetId());
}

bool TerrainAccessTester::Accessable(const GameUnitItem* gameUnitItem, const GameMapItem* gameMapItem)
{
	Q_ASSERT(gameUnitItem);
	Q_ASSERT(gameMapItem);

	const ModelUnitType* modelUnitType = gameUnitItem->GetModelUnitType();
	Q_ASSERT(modelUnitType);

	const ModelTerrainType* modelTerrainType = gameMapItem->GetTerrainType();
	Q_ASSERT(modelTerrainType);

	return modelUnitType->IsTerrainTypeAccessible(modelTerrainType->GetId());
}

#include "game/GameCityItem.h"
#include "model/ModelCityType.h"
bool TerrainAccessTester::Accessable(const ModelCityType* modelCityType, const int gameMapItemId)
{
	Q_ASSERT(modelCityType);

	GameMapItem* gameMapItem = GameMapItemRepository::GetInstance()->GetGameMapItemById(gameMapItemId);
	Q_ASSERT(gameMapItem);

	const ModelTerrainType* modelTerrainType = gameMapItem->GetTerrainType();
	Q_ASSERT(modelTerrainType);

	return modelCityType->IsPlaceableOnTerrainType(modelTerrainType->GetId());
}
