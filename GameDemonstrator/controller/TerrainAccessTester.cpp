#include "stdafx.h"
#include "TerrainAccessTester.h"
#include "game/GameUnit.h"
#include "game/GameMapTile.h"
#include "game/GameMapTileRepository.h"
#include "map/MapHexItem.h"
#include "model/ModelTerrainType.h"
#include "model/ModelUnitType.h"
#include "model/ModelCityTypeRepository.h"

bool TerrainAccessTester::Accessable(const ModelUnitType* modelUnitType, const int gameMapItemId)
{
	Q_ASSERT(modelUnitType);

	GameMapTile* gameMapItem = GameMapTileRepository::GetInstance()->GetById(gameMapItemId);
	Q_ASSERT(gameMapItem);

	const ModelTerrainType* modelTerrainType = gameMapItem->GetTerrainType();
	Q_ASSERT(modelTerrainType);

	return modelUnitType->IsTerrainTypeAccessible(modelTerrainType->GetId());
}

bool TerrainAccessTester::Accessable(const GameUnit* gameUnitItem, const MapHexItem* mapHexItem)
{
	Q_ASSERT(gameUnitItem);
	Q_ASSERT(mapHexItem);

	const ModelUnitType* modelUnitType = gameUnitItem->GetModelUnitType();
	Q_ASSERT(modelUnitType);

	const GameMapTile* gameMapItem = GameMapTileRepository::GetInstance()->GetById(mapHexItem->GetGameMapItemId());
	Q_ASSERT(gameMapItem);

	const ModelTerrainType* modelTerrainType = gameMapItem->GetTerrainType();
	Q_ASSERT(modelTerrainType);

	return modelUnitType->IsTerrainTypeAccessible(modelTerrainType->GetId());
}

bool TerrainAccessTester::Accessable(const GameUnit* gameUnitItem, const ModelTerrainType* modelTerrainType)
{
	Q_ASSERT(gameUnitItem);
	Q_ASSERT(modelTerrainType);

	const ModelUnitType* modelUnitType = gameUnitItem->GetModelUnitType();
	Q_ASSERT(modelUnitType);

	return modelUnitType->IsTerrainTypeAccessible(modelTerrainType->GetId());
}

bool TerrainAccessTester::Accessable(const GameUnit* gameUnitItem, const GameMapTile* gameMapItem)
{
	Q_ASSERT(gameUnitItem);
	Q_ASSERT(gameMapItem);

	const ModelUnitType* modelUnitType = gameUnitItem->GetModelUnitType();
	Q_ASSERT(modelUnitType);

	const ModelTerrainType* modelTerrainType = gameMapItem->GetTerrainType();
	Q_ASSERT(modelTerrainType);

	return modelUnitType->IsTerrainTypeAccessible(modelTerrainType->GetId());
}

#include "game/GameCity.h"
#include "model/ModelCityType.h"
bool TerrainAccessTester::Accessable(const ModelCityType* modelCityType, const int gameMapItemId)
{
	Q_ASSERT(modelCityType);

	GameMapTile* gameMapItem = GameMapTileRepository::GetInstance()->GetById(gameMapItemId);
	Q_ASSERT(gameMapItem);

	const ModelTerrainType* modelTerrainType = gameMapItem->GetTerrainType();
	Q_ASSERT(modelTerrainType);

	return modelCityType->IsPlaceableOnTerrainType(modelTerrainType->GetId());
}

bool TerrainAccessTester::Accessable(const int modelCityTypeId, const int gameMapItemId)
{
	const ModelCityType* modelCityType = ModelCityTypeRepository::GetInstance()->GetTypeById(modelCityTypeId);
	Q_ASSERT(modelCityType);

	GameMapTile* gameMapItem = GameMapTileRepository::GetInstance()->GetById(gameMapItemId);
	Q_ASSERT(gameMapItem);

	const ModelTerrainType* modelTerrainType = gameMapItem->GetTerrainType();
	Q_ASSERT(modelTerrainType);

	return modelCityType->IsPlaceableOnTerrainType(modelTerrainType->GetId());
}
