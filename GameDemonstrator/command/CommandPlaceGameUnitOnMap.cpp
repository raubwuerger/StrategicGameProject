#include "stdafx.h"
#include "CommandPlaceGameUnitOnMap.h"
#include "game\GameUnitRepository.h"
#include "game\GameMapTile.h"
#include "controller\TerrainAccessTester.h"
#include "map\MapUnitItemFactory.h"
#include "game\GameMapTileRepository.h"

MapView*	CommandPlaceGameUnitOnMap::MapViewObject = nullptr;

bool CommandPlaceGameUnitOnMap::PlaceGameUnit(const GameUnit* gameUnitItem, const GameMapTile* gameMapItem)
{
	Q_ASSERT(gameUnitItem);
	Q_ASSERT(gameMapItem);
	Q_ASSERT(MapViewObject);

	CommandPlaceGameUnitOnMap commandPlaceGameUnitOnMap;

	if (false == TerrainAccessTester::Accessable(gameUnitItem, gameMapItem))
	{
		return false;
	}

	MapUnitItemFactory mapUnitItemFactory;
	if (false == mapUnitItemFactory.Create(MapViewObject, gameUnitItem))
	{
		return false;
	}
	return true;
}

bool CommandPlaceGameUnitOnMap::PlaceGameUnit(const GameUnit* gameUnitItem, int gameMapItemId)
{
	return PlaceGameUnit(gameUnitItem, GameMapTileRepository::GetInstance()->GetById(gameMapItemId));
}
