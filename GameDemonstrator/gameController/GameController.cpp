#include "stdafx.h"
#include "GameController.h"
#include "map/MapView.h"
#include "map/MapUnitItemRepository.h"
#include "map/MapUnitItem.h"
#include "connectors/ConnectorMapUnitItem.h"
#include "gameconfig.h"
#include "model/ModelOwnerTypeRepository.h"
#include "model/ModelOwnerType.h"
#include "game/GameUnitItemRepository.h"
#include "game/GameUnitItem.h"

GameController::GameController()
	: Selected(nullptr)
{

}

void GameController::Init()
{
}

void GameController::ConnectSinglePlayer()
{
	disconnect(MapView::ConnectorMapUnitItemInstance, &ConnectorMapUnitItem::SignalUnitItemPressedLeftButton, this, &GameController::SlotGameUnitSelectedEditorMode);
	connect(MapView::ConnectorMapUnitItemInstance, &ConnectorMapUnitItem::SignalUnitItemPressedLeftButton, this, &GameController::SlotGameUnitSelected);
	connect(MapView::ConnectorMapUnitItemInstance, &ConnectorMapUnitItem::SignalUnitItemPressedRightButton, this, &GameController::SlotGameUnitUnselected);
}

void GameController::ConnectEditor()
{
	disconnect(MapView::ConnectorMapUnitItemInstance, &ConnectorMapUnitItem::SignalUnitItemPressedLeftButton, this, &GameController::SlotGameUnitSelected);
	connect(MapView::ConnectorMapUnitItemInstance, &ConnectorMapUnitItem::SignalUnitItemPressedLeftButton, this, &GameController::SlotGameUnitSelectedEditorMode);
	connect(MapView::ConnectorMapUnitItemInstance, &ConnectorMapUnitItem::SignalUnitItemPressedRightButton, this, &GameController::SlotGameUnitUnselected);
}

void GameController::Disconnect()
{
	disconnect(MapView::ConnectorMapUnitItemInstance, &ConnectorMapUnitItem::SignalUnitItemPressedLeftButton, this, &GameController::SlotGameUnitSelected);
	disconnect(MapView::ConnectorMapUnitItemInstance, &ConnectorMapUnitItem::SignalUnitItemPressedRightButton, this, &GameController::SlotGameUnitUnselected);
	disconnect(MapView::ConnectorMapUnitItemInstance, &ConnectorMapUnitItem::SignalUnitItemPressedLeftButton, this, &GameController::SlotGameUnitSelectedEditorMode);
}

bool GameController::InitGame()
{
	const ModelOwnerType* ownerType = ModelOwnerTypeRepository::GetInstance()->GetOwnerTypeById(GameConfig::PlayerId.toInt());
	if (nullptr == ownerType)
	{
		return false;
	}
	GameConfig::OwnerType = const_cast<ModelOwnerType*>(ownerType);
	return true;
}

void GameController::SlotGameUnitSelected(int gameUnitId)
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

void GameController::SlotGameUnitSelectedEditorMode(int gameUnitId)
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

bool GameController::IsUnitOfItsOwn(const MapUnitItem* mapUnitItem) const
{
	const GameUnitItem* gameUnitItem = GameUnitItemRepository::GetInstance()->GetGameUnitItemById(mapUnitItem->GetGameUnitId());
	Q_ASSERT(gameUnitItem);

	return GameConfig::OwnerType->operator==(*gameUnitItem->GetModelOwnerType());
}
