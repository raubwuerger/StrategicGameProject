#include "stdafx.h"
#include "UnitTypeEditor.h"
#include "model/ModelUnitTypeRepository.h"
#include "model/ModelUnitType.h"
#include "game/GameUnitItemRepository.h"
#include "game/GameUnitItemFactory.h"
#include "map/MapUnitItemFactory.h"
#include "map/MapView.h"
#include "map/MapUnitItem.h"
#include "LogInterface.h"
#include "controller/EditorController.h"

UnitTypeEditor::UnitTypeEditor(QObject *parent)
	: BaseEditor(parent),
	ActiveUnitType(nullptr),
	EditorControllerInstance(nullptr),
	MapViewInstance(nullptr),
	SELECTEDGAMEMAPITEM_NOT_INITIALIZED(-1),
	SelectedGameMapItem(SELECTEDGAMEMAPITEM_NOT_INITIALIZED),
	NO_UNITS(0),
	MAX_UNITS(1)
{

}

UnitTypeEditor::~UnitTypeEditor()
{

}

void UnitTypeEditor::SetMapView(MapView* mapView)
{
	MapViewInstance = mapView;
}

void UnitTypeEditor::SetEditorController(EditorController* editorController)
{
	EditorControllerInstance = editorController;
}

void UnitTypeEditor::SlotActiveUnitTypeId(int unitTypeId)
{
	ActiveUnitType = ModelUnitTypeRepository::GetInstance()->FindModelUnitTypeById(unitTypeId);
}

void UnitTypeEditor::SlotActivated()
{
	if (nullptr == EditorControllerInstance)
	{
		return;
	}
	EditorControllerInstance->Activate(this);
}

void UnitTypeEditor::SlotAddUnit(int mapHexItemId)
{
	SelectedGameMapItem = mapHexItemId;
	CreateUnit();
}

#include "game/GameUnitItem.h"
#include "controller/MapItemMapUnitMovementController.h"
void UnitTypeEditor::CreateUnit()
{
	if (false == IsUnitTypeEditorInitialzedForCreatingUnit())
	{
		return;
	}

	MapItemMapUnitMovementController mapItemMapUnitMovementController;
	if (false == mapItemMapUnitMovementController.IsTerrainTypeAccessible(ActiveUnitType, SelectedGameMapItem))
	{
		return;
	}

	GameUnitItemFactory gameUnitItemFactory;
	GameUnitItem* created = gameUnitItemFactory.CreateGameUnitItemFromScratch(ActiveUnitType,SelectedGameMapItem);

	if (nullptr == created)
	{
		jha::GetLog()->Log_MESSAGE(tr("Unable to create GameUnitItem from type %1!").arg(QString::number(ActiveUnitType->GetId())));
		return;
	}

	MapUnitItemFactory mapUnitItemFactory;
	if (false == mapUnitItemFactory.Create(MapViewInstance, created))
	{
		return;
	}
	jha::GetLog()->Log_DEBUG(tr("MapUnitItem (Id=%1) successfully created on HexItem (Id=%2)!").arg(QString::number(created->GetId())).arg(QString::number(SelectedGameMapItem)));
}

void UnitTypeEditor::SlotDeleteUnitFromMapHexItemId(int mapHexItemId)
{
	SelectedGameMapItem = mapHexItemId;
	DeleteUnit(mapHexItemId);
}

void UnitTypeEditor::SlotDeleteUnitFromGameUnitId(int gameUnitId)
{
	GameUnitItem* gameUnitItemToDelete = GameUnitItemRepository::GetInstance()->GetGameUnitItemById(gameUnitId);
	if (nullptr == gameUnitItemToDelete)
	{
		return;
	}
	SelectedGameMapItem = gameUnitItemToDelete->GetGameMapItemId();
	DeleteUnit(gameUnitItemToDelete->GetGameMapItemId());
}

#include "map/MapUnitItemRepository.h"
void UnitTypeEditor::DeleteUnit( int gameMapItemId )
{
	if (false == IsUnitTypeEditorInitialzedForDeletingUnit())
	{
		return;
	}

	GameUnitItem* gameUnitItemToDelete = GameUnitItemRepository::GetInstance()->RemoveGameUnitItemByGameMapItemId(gameMapItemId);
	if (nullptr == gameUnitItemToDelete)
	{
		jha::GetLog()->Log_FATAL(tr("No GameUnitItem registered for GameMapItemId %1!").arg(QString::number(gameMapItemId)));
		return;
	}

	MapUnitItem* mapUnitItemToDelete = MapUnitItemRepository::GetInstance()->Remove(gameUnitItemToDelete->GetId());
	if (nullptr == mapUnitItemToDelete)
	{
		delete gameUnitItemToDelete;
		jha::GetLog()->Log_FATAL(tr("No MapUnitItem registered for GameMapItemId %1!").arg(QString::number(gameMapItemId)));
		return;
	}

	if (false == MapViewInstance->RemoveMapUnit(mapUnitItemToDelete))
	{
		delete gameUnitItemToDelete;
		delete mapUnitItemToDelete;
		jha::GetLog()->Log_FATAL(tr("Unable to remove MapUnitItem from MapView with Id=%1!").arg(QString::number(mapUnitItemToDelete->GetGameUnitId())));
		return;
	}

	delete gameUnitItemToDelete;
	delete mapUnitItemToDelete;
	jha::GetLog()->Log_DEBUG(tr("MapUnitItem (Id=%1) successfully removed on HexItem (Id=%2)!").arg(QString::number(mapUnitItemToDelete->GetGameUnitId())).arg(QString::number(gameMapItemId)));
}

bool UnitTypeEditor::HasMapHexItemUnits() const
{
	return GameUnitItemRepository::GetInstance()->GetGameUnitItemsCountByGameMapItemId(SelectedGameMapItem);
}

bool UnitTypeEditor::IsSelectedGameMapItemInitialized() const
{
	return SELECTEDGAMEMAPITEM_NOT_INITIALIZED != SelectedGameMapItem;
}

bool UnitTypeEditor::IsUnitTypeEditorInitialzed() const
{
	if (nullptr == MapViewInstance)
	{
		jha::GetLog()->Log_MESSAGE(tr("Class member <MapViewInstance> is null! -> SetMapView()"));
		return false;
	}

	if (false == IsSelectedGameMapItemInitialized())
	{
		jha::GetLog()->Log_MESSAGE(tr("Class member <SelectedGameMapItem> is not initialized! -> SlotAddUnit()"));
		return false;
	}
	return true;
}

bool UnitTypeEditor::IsUnitTypeEditorInitialzedForCreatingUnit() const
{
	if (false == IsUnitTypeEditorInitialzed())
	{
		return false;
	}

	if (nullptr == ActiveUnitType)
	{
		jha::GetLog()->Log_MESSAGE(tr("Class member <ActiveUnitType> is null! -> SlotActiveUnitTypeId()"));
		return false;
	}

	if (true == HasMapHexItemUnits())
	{
		jha::GetLog()->Log_MESSAGE(tr("HexMapItem %1 already contains a UnitItem").arg(QString::number(SelectedGameMapItem)));
		return false;
	}

	return true;
}

bool UnitTypeEditor::IsUnitTypeEditorInitialzedForDeletingUnit() const
{
	if (false == IsUnitTypeEditorInitialzed())
	{
		return false;
	}

	if (false == HasMapHexItemUnits())
	{
		jha::GetLog()->Log_DEBUG(tr("HexMapItem %1 has no units to delete!").arg(QString::number(SelectedGameMapItem)));
		return false;  //No unit to delete;
	}

	return true;
}

