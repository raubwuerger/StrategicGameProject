#include "stdafx.h"
#include "MapUnitHelper.h"
#include "MapHexItemRepository.h"
#include "MapUnitItemRepository.h"
#include "MapUnitItem.h"
#include "MapHexItem.h"
#include "MapUnitItemFactory.h"
#include "game/GameUnit.h"
#include "game/GameUnitHelper.h"
#include "game/GameUnitFactory.h"
#include "game/GameUnitRepository.h"


MapUnitHelper::MapUnitHelper(GameUnit* gameUnit)
	: GameUnitToMove(gameUnit)
{
	Q_ASSERT(GameUnitToMove);
}

bool MapUnitHelper::Move(const MapHexItem* destMapHexItem)
{
	const MapHexItem*  sourceMapHexItem = MapHexItemRepository::GetInstance()->GetById(GameUnitHelper::GetMapHexItemId(GameUnitToMove));
	Q_ASSERT(sourceMapHexItem);

	MapUnitItem *mapUnitItem = MapUnitItemRepository::GetInstance()->GetById(GameUnitToMove->GetId());
	Q_ASSERT(mapUnitItem);
	mapUnitItem->SetMapHexItemId(destMapHexItem->GetId());
	mapUnitItem->SetMapHexItemId(destMapHexItem->GetId());
	mapUnitItem->setPos(destMapHexItem->GetTopLeftPoint() - MapUnitItemFactory::MAPHEXITEM_OFFSET);

	std::unique_ptr<GameUnitParameterObject> gameUnitParameterObject = CreateUpdateGameUnit(destMapHexItem);

	GameUnitFactory gameUnitItemFactory;
	GameUnit* movedGameUnitItem = gameUnitItemFactory.Update(*gameUnitParameterObject);
	GameUnitRepository::GetInstance()->UpdateGameUnitOnGameMapTile(movedGameUnitItem, sourceMapHexItem->GetId());

	if (false == movedGameUnitItem->Move())
	{
		return false;
	}

	if (false == GameUnitToMove->GetIsTransporter())
	{
		return true;
	}
	
	return MoveTransportedUnits(destMapHexItem);
}

std::unique_ptr<GameUnitParameterObject> MapUnitHelper::CreateUpdateGameUnit(const MapHexItem* destMapHexItem)
{
	std::unique_ptr<GameUnitParameterObject> gameUnitParameterObject(new GameUnitParameterObject);
	gameUnitParameterObject->GameUnitObject = GameUnitToMove;
	gameUnitParameterObject->GameOwnerObject = GameUnitToMove->GetGameOwner();
	gameUnitParameterObject->GameMapTileId = destMapHexItem->GetId();
	gameUnitParameterObject->ModelUnitTypeObject = GameUnitToMove->GetModelUnitType();
	return gameUnitParameterObject;
}

bool MapUnitHelper::MoveTransportedUnits(const MapHexItem* destMapHexItem)
{
	int transportedUnitsCount = GameUnitToMove->GetCountTransportedUnits();
	for (int index = 0; index < transportedUnitsCount; index++)
	{
		//TODO: Is casting a good idea? Or should the move operation be mutable?
		MapUnitHelper mapUnitHelper(const_cast<GameUnit*>(GameUnitToMove->GetTransportedUnitAt(index)));
		if (false == mapUnitHelper.Move(destMapHexItem))
		{
			return false;
		}
	}
	return true;
}

