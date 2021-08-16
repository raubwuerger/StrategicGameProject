#include "stdafx.h"
#include "KeyEventController.h"
#include "MapItemMapUnitMovementController.h"
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
#include "game/GameUnitItem.h"
bool KeyEventController::IsMovementDirectionValid(int movementDirection, MapUnitItem* mapUnitItem) const
{
	GameMapMoveInfo gameMapMoveInfo(mapUnitItem);
	const MapHexItem* destMapHexItem = gameMapMoveInfo.GetDestinationInfo(movementDirection);
	if (nullptr == destMapHexItem)
	{
		return false;
	}

	MapItemMapUnitMovementController mapItemMapUnitMovementController;
	if (false == mapItemMapUnitMovementController.CanUnitMove(destMapHexItem, mapUnitItem->GetGameUnitId()))
	{
		return false;
	}

	GameUnitItem* gameUnitItem = GameUnitItemRepository::GetInstance()->GetGameUnitItemById(mapUnitItem->GetGameUnitId());
	if (nullptr == gameUnitItem)
	{
		return false;
	}

	gameUnitItem->SetGameMapItemId(destMapHexItem->GetGameMapItemId());
	mapUnitItem->SetMapHexItemId(destMapHexItem->GetGameMapItemId());

	const MapHexItem*  sourceMapHexItem = MapHexItemRepository::GetInstance()->GetMapHexItemById(mapUnitItem->GetMapHexItemId());
		
/*	jha::GetLog()->Log_MESSAGE(QObject::tr("Source: %1|%2 - offset: %3|%4 - dest: %5|%6").arg(QString::number(source.width())).arg(QString::number(source.height()))
		.arg(QString::number(offset.width())).arg(QString::number(offset.height()))
		.arg(QString::number(destination.width())).arg(QString::number(destination.height())));
		*/

	const QPointF& sourceCenterPoint = sourceMapHexItem->GetCenterPoint();
	const QPointF& destCenterPoint = destMapHexItem->GetCenterPoint();
	QPointF offsetCenterPoint(destCenterPoint - sourceCenterPoint);
	mapUnitItem->moveBy(offsetCenterPoint.x(), offsetCenterPoint.y());
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

void KeyEventController::CreateValidMovementPositions(MapHexItem* mapHexItem)
{
	int col = mapHexItem->GetCol();
	int row = mapHexItem->GetRow();
}
