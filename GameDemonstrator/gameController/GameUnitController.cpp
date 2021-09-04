#include "stdafx.h"
#include "GameUnitController.h"
#include "map/MapView.h"
#include "map/MapUnitItemRepository.h"
#include "map/MapUnitItem.h"
#include "connectors/ConnectorMapUnitItem.h"
#include "gameconfig.h"
#include "model/ModelOwnerTypeRepository.h"
#include "model/ModelOwnerType.h"
#include "game/GameUnitItemRepository.h"
#include "game/GameUnitItem.h"

GameUnitController::GameUnitController()
	: Selected(nullptr)
{

}

void GameUnitController::Init()
{
}

void GameUnitController::ConnectSinglePlayer()
{
	disconnect(MapView::ConnectorMapUnitItemInstance, &ConnectorMapUnitItem::SignalUnitItemPressedLeftButton, this, &GameUnitController::SlotGameUnitSelectedEditorMode);
	connect(MapView::ConnectorMapUnitItemInstance, &ConnectorMapUnitItem::SignalUnitItemPressedLeftButton, this, &GameUnitController::SlotGameUnitSelected);
	connect(MapView::ConnectorMapUnitItemInstance, &ConnectorMapUnitItem::SignalUnitItemPressedRightButton, this, &GameUnitController::SlotGameUnitUnselected);
}

void GameUnitController::ConnectEditor()
{
	disconnect(MapView::ConnectorMapUnitItemInstance, &ConnectorMapUnitItem::SignalUnitItemPressedLeftButton, this, &GameUnitController::SlotGameUnitSelected);
	connect(MapView::ConnectorMapUnitItemInstance, &ConnectorMapUnitItem::SignalUnitItemPressedLeftButton, this, &GameUnitController::SlotGameUnitSelectedEditorMode);
	connect(MapView::ConnectorMapUnitItemInstance, &ConnectorMapUnitItem::SignalUnitItemPressedRightButton, this, &GameUnitController::SlotGameUnitUnselected);
}

void GameUnitController::Disconnect()
{
	disconnect(MapView::ConnectorMapUnitItemInstance, &ConnectorMapUnitItem::SignalUnitItemPressedLeftButton, this, &GameUnitController::SlotGameUnitSelected);
	disconnect(MapView::ConnectorMapUnitItemInstance, &ConnectorMapUnitItem::SignalUnitItemPressedRightButton, this, &GameUnitController::SlotGameUnitUnselected);
	disconnect(MapView::ConnectorMapUnitItemInstance, &ConnectorMapUnitItem::SignalUnitItemPressedLeftButton, this, &GameUnitController::SlotGameUnitSelectedEditorMode);
}

bool GameUnitController::InitGame()
{
	const ModelOwnerType* ownerType = GameConfig::PlayerOwnerType;
	if (nullptr == ownerType)
	{
		return false;
	}
	GameConfig::PlayerOwnerType = const_cast<ModelOwnerType*>(ownerType);
	return true;
}

void GameUnitController::SlotGameUnitSelected(int gameUnitId)
{
	MapUnitItem* mapUnitItem = MapUnitItemRepository::GetInstance()->GetMapUnitItem(gameUnitId);
	if (nullptr == mapUnitItem)
	{
		return;
	}

	if (false == IsUnitOfItsOwn(mapUnitItem))
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

void GameUnitController::SlotGameUnitUnselected(int gameUnitId)
{
	MapUnitItem* mapUnitItem = MapUnitItemRepository::GetInstance()->GetMapUnitItem(gameUnitId);
	if (nullptr == mapUnitItem)
	{
		return;
	}

	mapUnitItem->ShowOriginal();
	Selected = nullptr;
}

void GameUnitController::SlotGameUnitSelectedEditorMode(int gameUnitId)
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

bool GameUnitController::IsUnitOfItsOwn(const MapUnitItem* mapUnitItem) const
{
	const GameUnitItem* gameUnitItem = GameUnitItemRepository::GetInstance()->GetGameUnitItemById(mapUnitItem->GetGameUnitId());
	Q_ASSERT(gameUnitItem);

	return GameConfig::PlayerOwnerType->operator==(*gameUnitItem->GetModelOwnerType());
}
