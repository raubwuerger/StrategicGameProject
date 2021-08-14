#include "stdafx.h"
#include "KeyEventController.h"
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
		if (false == IsMovementDirectionValid(1, mapUnitItem))
		{
			return;
		}

		mapUnitItem->moveBy(-72, 42);
		return;
	}
	if (Qt::Key_2 == keyEvent->key())
	{
		if (false == IsMovementDirectionValid(2, mapUnitItem))
		{
			return;
		}
		mapUnitItem->moveBy(0, 83);
		return;
	}
	if (Qt::Key_3 == keyEvent->key())
	{
		if (false == IsMovementDirectionValid(3, mapUnitItem))
		{
			return;
		}
		mapUnitItem->moveBy(72, 42);
		return;
	}
	if (Qt::Key_7 == keyEvent->key())
	{
		if (false == IsMovementDirectionValid(7, mapUnitItem))
		{
			return;
		}
		mapUnitItem->moveBy(-72, -42);
		return;
	}
	if (Qt::Key_8 == keyEvent->key())
	{
		if (false == IsMovementDirectionValid(8, mapUnitItem))
		{
			return;
		}
		mapUnitItem->moveBy(0, -83);
		return;
	}
	if (Qt::Key_9 == keyEvent->key())
	{
		if (false == IsMovementDirectionValid(9, mapUnitItem))
		{
			return;
		}
		mapUnitItem->moveBy(72, -42);
		return;
	}

	if (Qt::Key_Escape == keyEvent->key())
	{
		mapUnitItem->setSelected(false);
		return;
	}
}

#include "game/GameUnitItemRepository.h"
#include "game/GameUnitItem.h"
bool KeyEventController::IsMovementDirectionValid(int movementDirection, MapUnitItem* mapUnitItem) const
{
	int mapHexItemId = mapUnitItem->GetMapHexItemId();

	MapHexItem* mapHexItem = MapHexItemRepository::GetInstance()->GetMapHexItemById(mapHexItemId);
	if(nullptr == mapHexItem)
	{
		return false;
	}
	const QPointF& mapHexItemCenterPoint = mapHexItem->GetCenterPoint();

	int isEvenInt = mapHexItem->GetCol() % 2;
	const QSize source(mapHexItem->GetRow(), mapHexItem->GetCol());
	if (0 == isEvenInt)
	{
		if (false == MovementTypeColumEven.contains(movementDirection))
		{
			return false;
		}
		QSize offset = MovementTypeColumEven[movementDirection];
		QSize destination = source + offset;
		MapHexItem* destinationMapHexItem = MapHexItemRepository::GetInstance()->GetMapHexItemByRowCol(destination.width(), destination.height());
		if (nullptr == destinationMapHexItem)
		{
			return false;
		}
		GameUnitItem* gameUnitItem = GameUnitItemRepository::GetInstance()->GetGameUnitItemById(mapUnitItem->GetGameUnitId());
		if (nullptr == gameUnitItem)
		{
			return false;
		}
		gameUnitItem->SetGameMapItemId(destinationMapHexItem->GetGameMapItemId());
		mapUnitItem->SetMapHexItemId(destinationMapHexItem->GetGameMapItemId());
		jha::GetLog()->Log_MESSAGE(QObject::tr("Source: %1|%2 - offset: %3|%4 - dest: %5|%6").arg(QString::number(source.width())).arg(QString::number(source.height()))
			.arg(QString::number(offset.width())).arg(QString::number(offset.height()))
			.arg(QString::number(destination.width())).arg(QString::number(destination.height())));
		return true;
	}
	if (1 == isEvenInt)
	{
		if (false == MovementTypeColumOdd.contains(movementDirection))
		{
			return false;
		}
		QSize offset = MovementTypeColumOdd[movementDirection];
		QSize destination = source + offset;
		MapHexItem* destinationMapHexItem = MapHexItemRepository::GetInstance()->GetMapHexItemByRowCol(destination.width(), destination.height());
		if (nullptr == destinationMapHexItem)
		{
			return false;
		}
		GameUnitItem* gameUnitItem = GameUnitItemRepository::GetInstance()->GetGameUnitItemById(mapUnitItem->GetGameUnitId());
		if (nullptr == gameUnitItem)
		{
			return false;
		}
		jha::GetLog()->Log_MESSAGE(QObject::tr("Source: %1|%2 - offset: %3|%4 - dest: %5|%6").arg(QString::number(source.width())).arg(QString::number(source.height()))
			.arg(QString::number(offset.width())).arg(QString::number(offset.height()))
			.arg(QString::number(destination.width())).arg(QString::number(destination.height())));
		gameUnitItem->SetGameMapItemId(destinationMapHexItem->GetGameMapItemId());
		mapUnitItem->SetMapHexItemId(destinationMapHexItem->GetGameMapItemId());
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
	MovementTypeColumEven.insert(3, QSize(0, +1));

	MovementTypeColumOdd.insert(7, QSize(0, -1));
	MovementTypeColumOdd.insert(8, QSize(-1, 0));
	MovementTypeColumOdd.insert(9, QSize(0, 1));
	MovementTypeColumOdd.insert(1, QSize(+1, -1));
	MovementTypeColumOdd.insert(2, QSize(+1, 0));
	MovementTypeColumOdd.insert(3, QSize(+1, +1));
}
