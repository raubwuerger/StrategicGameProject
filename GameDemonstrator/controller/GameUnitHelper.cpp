#include "stdafx.h"
#include "GameUnitHelper.h"

#include "game\GameUnit.h"
#include "game\GameUnitRepository.h"

#include "map\MapUnitItemRepository.h"
#include "map\MapUnitItem.h"

bool GameUnitHelper::IsEnemyOnDestinationMapTile(const GameUnit* gameUnitSource, int gameMapItemId)
{
	const GameUnit* gameUnitDestination = GameUnitRepository::GetInstance()->GetByGameMapTileId(gameMapItemId);
	if (nullptr == gameUnitDestination)
	{
		return false;
	}
	return gameUnitDestination->GetGameOwner() != gameUnitSource->GetGameOwner();
}

bool GameUnitHelper::IsOwnUnitOnDestinationMapTile(const GameUnit* gameUnitSource, int gameMapItemId)
{
	const GameUnit* gameUnitDestination = GameUnitRepository::GetInstance()->GetByGameMapTileId(gameMapItemId);
	if (nullptr == gameUnitDestination)
	{
		return false;
	}
	return gameUnitDestination->GetGameOwner() == gameUnitSource->GetGameOwner();
}

int GameUnitHelper::GetMapHexItemId(const GameUnit* gameUnit)
{
	const MapUnitItem* mapUnitItem = MapUnitItemRepository::GetInstance()->GetById(gameUnit->GetId());
	Q_ASSERT(mapUnitItem);
	return mapUnitItem->GetMapHexItemId();
}

const GameUnit* GameUnitHelper::GetEnemyGameUnit(int mapItemId)
{
	return GameUnitRepository::GetInstance()->GetByGameMapTileId(mapItemId);
}
