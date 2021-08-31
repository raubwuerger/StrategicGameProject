#include "stdafx.h"
#include "GameController.h"
#include "map/MapView.h"
#include "map/MapUnitItemRepository.h"
#include "map/MapUnitItem.h"
#include "connectors/ConnectorMapUnitItem.h"

GameController::GameController()
	: Selected(nullptr)
{

}

void GameController::Init()
{
	connect(MapView::ConnectorMapUnitItemInstance, &ConnectorMapUnitItem::SignalUnitItemPressedLeftButton, this, &GameController::SlotGameUnitSelected );
	connect(MapView::ConnectorMapUnitItemInstance, &ConnectorMapUnitItem::SignalUnitItemPressedRightButton, this, &GameController::SlotGameUnitUnselected);
}

void GameController::SlotGameUnitSelected(int gameUnitId)
{
	MapUnitItem* mapUnitItem = MapUnitItemRepository::GetInstance()->GetMapUnitItem(gameUnitId);
	if (nullptr == mapUnitItem)
	{
		return;
	}

	if (nullptr != Selected)
	{
		Selected->ShowOriginal();
	}

	Selected = mapUnitItem;
	mapUnitItem->ShowSelected();
}

void GameController::SlotGameUnitUnselected(int gameUnitId)
{
	MapUnitItem* mapUnitItem = MapUnitItemRepository::GetInstance()->GetMapUnitItem(gameUnitId);
	if (nullptr == mapUnitItem)
	{
		return;
	}

	mapUnitItem->ShowOriginal();
	Selected = nullptr;
}
