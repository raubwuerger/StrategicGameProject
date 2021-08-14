#include "stdafx.h"
#include "KeyEventController.h"
#include "map\MapUnitItem.h"
#include "map\MapHexItemRepository.h"
#include "map\MapHexItem.h"

QMap<int, QSize> KeyEventController::MovementTypeColumEven;
QMap<int, QSize> KeyEventController::MovementTypeColumOdd;

KeyEventController::KeyEventController()
{
	CreateMovementTypes();
}

void KeyEventController::HandleKeyPressEvent(MapUnitItem* mapUnitItem, QKeyEvent* keyEvent)
{
	int mapHexItemId = mapUnitItem->GetMapHexItemId();

	MapHexItem* mapHexItem = MapHexItemRepository::GetInstance()->GetMapHexItemById(mapHexItemId);
	const QPointF& mapHexItemCenterPoint = mapHexItem->GetCenterPoint();

	if (Qt::Key_1 == keyEvent->key())
	{
		if (false == IsMovementDirectionValid(1, mapHexItem))
		{
			return;
		}

		mapUnitItem->moveBy(-72, 42);
		return;
	}
	if (Qt::Key_2 == keyEvent->key())
	{
		mapUnitItem->moveBy(0, 83);
		return;
	}
	if (Qt::Key_3 == keyEvent->key())
	{
		mapUnitItem->moveBy(72, 42);
		return;
	}
	if (Qt::Key_7 == keyEvent->key())
	{
		mapUnitItem->moveBy(-72, -42);
		return;
	}
	if (Qt::Key_8 == keyEvent->key())
	{
		mapUnitItem->moveBy(0, -83);
		return;
	}
	if (Qt::Key_9 == keyEvent->key())
	{
		mapUnitItem->moveBy(72, -42);
		return;
	}

	if (Qt::Key_Escape == keyEvent->key())
	{
		mapUnitItem->setSelected(false);
		return;
	}
}

bool KeyEventController::IsMovementDirectionValid(int movementDirection, const MapHexItem* mapHexItem) const
{
	bool isEven = mapHexItem->GetCol() % 2;
	const QSize source(mapHexItem->GetRow(), mapHexItem->GetCol());
	if (true == isEven)
	{
		if (false == MovementTypeColumEven.contains(movementDirection))
		{
			return false;
		}
		QSize movementDirectionOffset = MovementTypeColumEven[movementDirection];
		QSize destination = source + movementDirectionOffset;
		MapHexItem* destinationMapHexItem = MapHexItemRepository::GetInstance()->GetMapHexItemByRowCol(destination.width(), destination.height());
		if (nullptr == destinationMapHexItem)
		{
			return false;
		}
		return true;
	}
	if (false == isEven)
	{
		if (false == MovementTypeColumOdd.contains(movementDirection))
		{
			return false;
		}
		QSize movementDirectionOffset = MovementTypeColumOdd[movementDirection];
		QSize destination = source + movementDirectionOffset;
		MapHexItem* destinationMapHexItem = MapHexItemRepository::GetInstance()->GetMapHexItemByRowCol(destination.width(), destination.height());
		if (nullptr == destinationMapHexItem)
		{
			return false;
		}
		return true;
	}

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
	MovementTypeColumEven.insert(9, QSize(0, +1));

	MovementTypeColumOdd.insert(7, QSize(0, -1));
	MovementTypeColumOdd.insert(8, QSize(-1, 0));
	MovementTypeColumOdd.insert(9, QSize(0, 1));
	MovementTypeColumOdd.insert(1, QSize(+1, -1));
	MovementTypeColumOdd.insert(2, QSize(+1, 0));
	MovementTypeColumOdd.insert(3, QSize(+1, +1));
}
