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
		IsMovementDirectionValid(1, mapUnitItem);
		return;
	}
	if (Qt::Key_2 == keyEvent->key())
	{
		IsMovementDirectionValid(2, mapUnitItem);
		return;
	}
	if (Qt::Key_3 == keyEvent->key())
	{
		IsMovementDirectionValid(3, mapUnitItem);
		return;
	}
	if (Qt::Key_7 == keyEvent->key())
	{
		IsMovementDirectionValid(7, mapUnitItem);
		return;
	}
	if (Qt::Key_8 == keyEvent->key())
	{
		IsMovementDirectionValid(8, mapUnitItem);
		return;
	}
	if (Qt::Key_9 == keyEvent->key())
	{
		IsMovementDirectionValid(9, mapUnitItem);
		return;
	}
}

#include "game/GameUnitItemRepository.h"
#include "game/GameUnitItemFactory.h"
#include "game/GameUnitItem.h"
bool KeyEventController::IsMovementDirectionValid(int movementDirection, MapUnitItem* mapUnitItem) const
{
	GameMapMoveInfo gameMapMoveInfo(mapUnitItem);
	const MapHexItem* destMapHexItem = gameMapMoveInfo.GetDestinationInfo(movementDirection);
	if (nullptr == destMapHexItem)
	{
		return false;
	}

	GameUnitMovementController mapItemMapUnitMovementController(destMapHexItem);
	if (false == mapItemMapUnitMovementController.CanUnitMove(mapUnitItem->GetGameUnitId(), destMapHexItem))
	{
		return false;
	}

	GameUnitItem* sourceUnitItem = GameUnitItemRepository::GetInstance()->GetGameUnitItemById(mapUnitItem->GetGameUnitId());
	if (nullptr == sourceUnitItem)
	{
		return false;
	}
	
	GameUnitParameterObject gameUnitParameterObject;
	gameUnitParameterObject.GameUnitItemObject = sourceUnitItem;
	gameUnitParameterObject.ModelOwnerTypeObject = sourceUnitItem->GetModelOwnerType();
	gameUnitParameterObject.GameMapItemId = destMapHexItem->GetGameMapItemId();
	gameUnitParameterObject.ModelUnitTypeObject = sourceUnitItem->GetModelUnitType();
	
	const MapHexItem*  sourceMapHexItem = MapHexItemRepository::GetInstance()->GetMapHexItemById(mapUnitItem->GetMapHexItemId());

	mapUnitItem->SetMapHexItemId(destMapHexItem->GetGameMapItemId());

	GameUnitItemFactory gameUnitItemFactory;
	GameUnitItem* movedGameUnitItem = gameUnitItemFactory.UpdateGameUnitItem(gameUnitParameterObject);

	const QPointF& sourceCenterPoint = sourceMapHexItem->GetCenterPoint();
	const QPointF& destCenterPoint = destMapHexItem->GetCenterPoint();
	QPointF offsetCenterPoint(destCenterPoint - sourceCenterPoint);
	mapUnitItem->moveBy(offsetCenterPoint.x(), offsetCenterPoint.y());
	GameUnitItemRepository::GetInstance()->UpdateGameUnitItemsOnGameMapItem(movedGameUnitItem, sourceMapHexItem->GetGameMapItemId());
	return true;
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

