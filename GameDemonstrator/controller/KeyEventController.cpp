#include "stdafx.h"
#include "KeyEventController.h"
#include "GameUnitMovementController.h"
#include "map\MapUnitItem.h"
#include "map\MapHexItemRepository.h"
#include "map\MapHexItem.h"
#include "map\MapUnitItemRepository.h"
#include "LogInterface.h"
#include "controller\GameMapMoveInfo.h"

KeyEventController::KeyEventController()
{
	GameMapMoveInfo::CreateMovementTypes();
}

void KeyEventController::HandleKeyPressEvent(MapUnitItem* mapUnitItem, QKeyEvent* keyEvent)
{
	if (Qt::Key_1 == keyEvent->key())
	{
		MoveToDirection(1, mapUnitItem);
		return;
	}
	if (Qt::Key_2 == keyEvent->key())
	{
		MoveToDirection(2, mapUnitItem);
		return;
	}
	if (Qt::Key_3 == keyEvent->key())
	{
		MoveToDirection(3, mapUnitItem);
		return;
	}
	if (Qt::Key_7 == keyEvent->key())
	{
		MoveToDirection(7, mapUnitItem);
		return;
	}
	if (Qt::Key_8 == keyEvent->key())
	{
		MoveToDirection(8, mapUnitItem);
		return;
	}
	if (Qt::Key_9 == keyEvent->key())
	{
		MoveToDirection(9, mapUnitItem);
		return;
	}
}

#include "game/GameUnitRepository.h"
#include "game/GameUnitFactory.h"
#include "game/GameUnit.h"
bool KeyEventController::MoveToDirection(int movementDirection, MapUnitItem* mapUnitItem) const
{
	GameMapMoveInfo gameMapMoveInfo(mapUnitItem);
	const MapHexItem* destMapHexItem = gameMapMoveInfo.GetDestinationInfo(movementDirection);
	if (nullptr == destMapHexItem)
	{
		return false;
	}

	GameUnit* sourceUnitItem = GameUnitRepository::GetInstance()->GetById(mapUnitItem->GetGameUnitId());
	if (nullptr == sourceUnitItem)
	{
		return false;
	}

	GameUnitMovementController mapItemMapUnitMovementController(sourceUnitItem);
	if (false == mapItemMapUnitMovementController.CanUnitMoveToDestination(mapUnitItem->GetGameUnitId(), destMapHexItem))
	{
		return false;
	}
	
	GameUnitParameterObject gameUnitParameterObject;
	gameUnitParameterObject.GameUnitObject = sourceUnitItem;
	gameUnitParameterObject.GameOwnerObject = sourceUnitItem->GetGameOwner();
	gameUnitParameterObject.GameMapTileId = destMapHexItem->GetId();
	gameUnitParameterObject.ModelUnitTypeObject = sourceUnitItem->GetModelUnitType();
	
	const MapHexItem*  sourceMapHexItem = MapHexItemRepository::GetInstance()->GetById(mapUnitItem->GetMapHexItemId());

	mapUnitItem->SetMapHexItemId(destMapHexItem->GetId());

	GameUnitFactory gameUnitItemFactory;
	GameUnit* movedGameUnitItem = gameUnitItemFactory.Update(gameUnitParameterObject);

	//TODO: Kann man auch anders L�sen, indem man gleich den CenterPoint des Ziel-Kartenteils nimmt
	const QPointF& sourceCenterPoint = sourceMapHexItem->GetCenterPoint();
	const QPointF& destCenterPoint = destMapHexItem->GetCenterPoint();
	QPointF offsetCenterPoint(destCenterPoint - sourceCenterPoint);
	mapUnitItem->moveBy(offsetCenterPoint.x(), offsetCenterPoint.y());
	GameUnitRepository::GetInstance()->UpdateGameUnitOnGameMapTile(movedGameUnitItem, sourceMapHexItem->GetId());
	return movedGameUnitItem->Move();
}

void KeyEventController::HandleKeyReleaseEvent(MapUnitItem* mapUnitItem, QKeyEvent* keyEvent)
{
	if (Qt::Key_1 == keyEvent->key())
	{
		return;
	}
	if (Qt::Key_2 == keyEvent->key())
	{
		return;
	}
	if (Qt::Key_3 == keyEvent->key())
	{
		return;
	}
	if (Qt::Key_7 == keyEvent->key())
	{
		return;
	}
	if (Qt::Key_8 == keyEvent->key())
	{
		return;
	}
	if (Qt::Key_9 == keyEvent->key())
	{
		return;
	}
}

