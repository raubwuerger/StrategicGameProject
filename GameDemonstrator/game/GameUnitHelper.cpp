#include "stdafx.h"
#include "GameUnitHelper.h"
#include "GameUnit.h"
#include "GameMapTileRepository.h"
#include "GameUnitRepository.h"

#include "map\MapUnitItemRepository.h"
#include "map\MapUnitItem.h"

#include "model\ModelUnitType.h"


bool GameUnitHelper::IsEnemyOnDestinationMapTile(const GameUnit* gameUnitSource, int gameMapItemId)
{
	const GameUnit* gameUnitDestination = GameUnitRepository::GetInstance()->GetFirstGameUnitByGameMapTileId(gameMapItemId);
	if (nullptr == gameUnitDestination)
	{
		return false;
	}
	return gameUnitDestination->GetGameOwner() != gameUnitSource->GetGameOwner();
}

bool GameUnitHelper::IsOwnUnitOnDestinationMapTile(const GameUnit* gameUnitSource, int gameMapItemId)
{
	const GameUnit* gameUnitDestination = GameUnitRepository::GetInstance()->GetFirstGameUnitByGameMapTileId(gameMapItemId);
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
	return GameUnitRepository::GetInstance()->GetFirstGameUnitByGameMapTileId(mapItemId);
}

bool GameUnitHelper::IsTransporter(const GameUnit* gameUnit)
{
	Q_ASSERT(gameUnit);
	const ModelUnitType* unitType = gameUnit->GetModelUnitType();
	Q_ASSERT(unitType);
	return unitType->GetTransportCapacityStupid() > 0;
}

GameUnitHelper::GameUnitHelper(GameUnit* gameUnit)
	: GameUnitObject(GameUnitObject)
{
	Q_ASSERT(gameUnit);
	GameUnitObject = gameUnit;
}

bool GameUnitHelper::MoveToPosition(int mapId)
{
	Q_ASSERT(mapId >= 0);
	SetNewMapId(mapId);
	Q_ASSERT(GameUnitObject->GameMapTileObject);

	if (true == GameUnitObject->GetIsTransporter())
	{
		MoveTransportedUnits(mapId);
	}
	return true;
}

void GameUnitHelper::SetNewMapId(int mapId)
{
	GameUnitObject->MapTileId = mapId;
	GameUnitObject->GameMapTileObject = GameMapTileRepository::GetInstance()->GetById(mapId);
}

void GameUnitHelper::MoveTransportedUnits(int mapId)
{
	for (int i = 0; i < GameUnitObject->GetCountTransportedUnits(); i++)
	{
		//TODO: Is casting a good idea? Or should the move operation be mutable?
		GameUnitHelper tempGameUnitHelper(const_cast<GameUnit*>(GameUnitObject->GetTransportedUnitAt(i)));
		tempGameUnitHelper.MoveToPosition(mapId);
	}
}

