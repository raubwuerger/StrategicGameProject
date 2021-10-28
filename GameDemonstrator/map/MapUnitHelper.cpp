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
	return movedGameUnitItem->Move();
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

