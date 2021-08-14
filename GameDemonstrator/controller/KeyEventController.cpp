#include "stdafx.h"
#include "KeyEventController.h"
#include "MapItemMapUnitMovementController.h"
#include "map\MapUnitItem.h"
#include "map\MapHexItemRepository.h"
#include "map\MapHexItem.h"
#include "map\MapUnitItemRepository.h"
#include "LogInterface.h"

QMap<int, QSize> KeyEventController::MovementTypeColumEven;
QMap<int, QSize> KeyEventController::MovementTypeColumOdd;

KeyEventController::KeyEventController()
{
	CreateMovementTypes();
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
	MapHexItem* sourceMapHexItem = MapHexItemRepository::GetInstance()->GetMapHexItemById(mapUnitItem->GetMapHexItemId());
	if(nullptr == sourceMapHexItem)
	{
		return false;
	}
	QSize offset = GetCorrectOffset(movementDirection,sourceMapHexItem);

	GameUnitItem* gameUnitItem = GameUnitItemRepository::GetInstance()->GetGameUnitItemById(mapUnitItem->GetGameUnitId());
	if (nullptr == gameUnitItem)
	{
		return false;
	}

	const QSize source(sourceMapHexItem->GetRow(), sourceMapHexItem->GetCol());
	QSize destination = source + offset;
	MapHexItem* destinationMapHexItem = MapHexItemRepository::GetInstance()->GetMapHexItemByRowCol(destination.width(), destination.height());
	if (nullptr == destinationMapHexItem)
	{
		return false;
	}

	MapHexItem* destMapHexItem = MapHexItemRepository::GetInstance()->GetMapHexItemById(destinationMapHexItem->GetGameMapItemId());
	if (nullptr == destMapHexItem)
	{
		return false;
	}

	MapItemMapUnitMovementController mapItemMapUnitMovementController;
	if (false == mapItemMapUnitMovementController.CanUnitMove(destMapHexItem, gameUnitItem))
	{
		return false;
	}

	gameUnitItem->SetGameMapItemId(destinationMapHexItem->GetGameMapItemId());
	mapUnitItem->SetMapHexItemId(destinationMapHexItem->GetGameMapItemId());
	jha::GetLog()->Log_MESSAGE(QObject::tr("Source: %1|%2 - offset: %3|%4 - dest: %5|%6").arg(QString::number(source.width())).arg(QString::number(source.height()))
		.arg(QString::number(offset.width())).arg(QString::number(offset.height()))
		.arg(QString::number(destination.width())).arg(QString::number(destination.height())));


	const QPointF& sourceCenterPoint = sourceMapHexItem->GetCenterPoint();
	const QPointF& destCenterPoint = destMapHexItem->GetCenterPoint();
	QPointF offsetCenterPoint(destCenterPoint - sourceCenterPoint);
	mapUnitItem->moveBy(offsetCenterPoint.x(), offsetCenterPoint.y());
	return true;
}

QSize KeyEventController::GetCorrectOffset(int movementDirection, const MapHexItem* mapHexItem) const
{
	int isEvenInt = mapHexItem->GetCol() % 2;
	if (0 == isEvenInt)
	{
		return MovementTypeColumEven[movementDirection];
	}

	return MovementTypeColumOdd[movementDirection];
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

void KeyEventController::CreateMovementTypes()
{
	MovementTypeColumEven.insert(7, QSize(-1, -1));
	MovementTypeColumEven.insert(8, QSize(-1, 0));
	MovementTypeColumEven.insert(9, QSize(-1, 1));
	MovementTypeColumEven.insert(1, QSize(0, -1));
	MovementTypeColumEven.insert(2, QSize(+1, 0));
	MovementTypeColumEven.insert(3, QSize(0, +1));

	MovementTypeColumOdd.insert(7, QSize(0, -1));
	MovementTypeColumOdd.insert(8, QSize(-1, 0));
	MovementTypeColumOdd.insert(9, QSize(0, 1));
	MovementTypeColumOdd.insert(1, QSize(+1, -1));
	MovementTypeColumOdd.insert(2, QSize(+1, 0));
	MovementTypeColumOdd.insert(3, QSize(+1, +1));
}
