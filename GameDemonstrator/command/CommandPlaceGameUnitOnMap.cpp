#include "stdafx.h"
#include "CommandPlaceGameUnitOnMap.h"
#include "game\GameUnitItemRepository.h"
#include "game\GameMapItem.h"
#include "controller\TerrainAccessTester.h"
#include "map\MapUnitItemFactory.h"
#include "game\GameMapItemRepository.h"

MapView*	CommandPlaceGameUnitOnMap::MapViewObject = nullptr;

bool CommandPlaceGameUnitOnMap::PlaceGameUnit(const GameUnitItem* gameUnitItem, const GameMapItem* gameMapItem)
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

bool CommandPlaceGameUnitOnMap::PlaceGameUnit(const GameUnitItem* gameUnitItem, int gameMapItemId)
{
	return PlaceGameUnit(gameUnitItem, GameMapItemRepository::GetInstance()->GetGameMapItemById(gameMapItemId));
}
