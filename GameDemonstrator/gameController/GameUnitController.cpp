#include "stdafx.h"
#include "GameUnitController.h"
#include "map/MapView.h"
#include "map/MapUnitItemRepository.h"
#include "map/MapUnitItem.h"
#include "connectors/ConnectorMapUnitItem.h"
#include "game\gameconfig.h"
#include "model/ModelOwnerTypeRepository.h"
#include "game/GameOwner.h"
#include "game/GameUnitRepository.h"
#include "game/GameUnit.h"
#include "game/GameUnitRuntimeData.h"

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
	connect(MapView::ConnectorMapUnitItemInstance, &ConnectorMapUnitItem::SignalUnitItemPressedRightButton, this, &GameUnitController::SlotShowEmbarkedUnit);
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
	Selected = nullptr;
	GameOwner* ownerType = GameConfig::Player;
	if (nullptr == ownerType)
	{
		return false;
	}
	return true;
}

void GameUnitController::SlotGameUnitSelected(int gameUnitId)
{
	MapUnitItem* mapUnitItem = MapUnitItemRepository::GetInstance()->GetById(gameUnitId);
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
	MapUnitItem* mapUnitItem = MapUnitItemRepository::GetInstance()->GetById(gameUnitId);
	if (nullptr == mapUnitItem)
	{
		return;
	}

	mapUnitItem->ShowOriginal();
	Selected = nullptr;
}

void GameUnitController::SlotShowEmbarkedUnit(int gameUnitId)
{
	GameUnit* gameUnitClicked = GameUnitRepository::GetInstance()->GetById(gameUnitId);
	if (nullptr == gameUnitClicked)
	{
		Q_ASSERT(false);
		return;
	}

	if (gameUnitClicked->GetRuntimeData()->TransportedGameUnitIds.size() > 0)
	{
		GameUnit* embarkedUnit = gameUnitClicked->GetRuntimeData()->TransportedGameUnitIds[0];
		bool showed = MapUnitItemRepository::GetInstance()->Show(embarkedUnit->GetId());
		bool hided = MapUnitItemRepository::GetInstance()->Hide(gameUnitId);
		return;
	}

	if (true == gameUnitClicked->GetIsEmbarked() )
	{
		bool showed = MapUnitItemRepository::GetInstance()->Show(gameUnitClicked->GetIsEmbarkedOn()->GetId());
		bool hided = MapUnitItemRepository::GetInstance()->Hide(gameUnitClicked->GetId());
		return;
	}
	return;
}

void GameUnitController::SlotGameUnitSelectedEditorMode(int gameUnitId)
{
	MapUnitItem* mapUnitItem = MapUnitItemRepository::GetInstance()->GetById(gameUnitId);
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
	const GameUnit* gameUnitItem = GameUnitRepository::GetInstance()->GetById(mapUnitItem->GetGameUnitId());
	Q_ASSERT(gameUnitItem);

	return GameConfig::Player->operator==(*gameUnitItem->GetGameOwner());
}
