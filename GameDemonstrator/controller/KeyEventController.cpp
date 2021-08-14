#include "stdafx.h"
#include "KeyEventController.h"
#include "map\MapUnitItem.h"

void KeyEventController::HandleKeyPressEvent(MapUnitItem* mapUnitItem, QKeyEvent* keyEvent)
{
	if (Qt::Key_1 == keyEvent->key())
	{
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
