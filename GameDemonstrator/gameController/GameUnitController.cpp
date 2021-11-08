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
#include "game/GameUnitTransportContainer.h"

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
	if (nullptr == Selected)
	{
		return;
	}

	if (Selected->GetGameUnitId() == mapUnitItem->GetGameUnitId())
	{
		Selected = nullptr;
	}
}

void GameUnitController::SlotShowEmbarkedUnit(int gameUnitId)
{
	const GameUnit* gameUnitClicked = GameUnitRepository::GetInstance()->GetById(gameUnitId);
	const GameUnit* transporter = GameUnitRepository::GetInstance()->GetTransporterUnitByGameMapTileId(gameUnitClicked->GetGameTileId());
	if (nullptr == transporter)
	{
		return;
	}

	const GameUnit* selected = transporter->GetUnitTransportContainer()->SelectNextUnit();
	QVector<const GameUnit*> notSelected = transporter->GetUnitTransportContainer()->GetNotSelectedUnits();

	for (int index = 0; index < notSelected.size(); index++)
	{
		MapUnitItemRepository::GetInstance()->Hide(notSelected.at(index)->GetId());
	}

	MapUnitItemRepository::GetInstance()->Show(selected->GetId());
	SlotGameUnitSelected(selected->GetId());
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
