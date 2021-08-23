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
#include "controller/TerrainAccessTester.h"

UnitTypeEditor::UnitTypeEditor(QObject *parent)
	: BaseEditor(parent),
	ActiveModelUnitType(nullptr),
	EditorControllerInstance(nullptr),
	MapViewInstance(nullptr),
	VALUE_NOT_INITIALIZED(-1),
	ActiveGameMapItemId(VALUE_NOT_INITIALIZED),
	ActiveGameOwnerItemId(VALUE_NOT_INITIALIZED),
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

void UnitTypeEditor::SlotDeactivated()
{
	return; //TODO: Do nothing at the moment
}

void UnitTypeEditor::SlotActiveUnitTypeId(int unitTypeId)
{
	ActiveModelUnitType = ModelUnitTypeRepository::GetInstance()->GetModelUnitTypeById(unitTypeId);
}

void UnitTypeEditor::SlotActiveOwnerTypeId(int ownerTypeId)
{
	ActiveGameOwnerItemId = ownerTypeId;
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
	if (false == BaseEditor::GetActive())
	{
		return;
	}

	ActiveGameMapItemId = mapHexItemId;
	CreateUnit();
}

#include "game/GameUnitItem.h"
#include "controller/GameUnitMovementController.h"
#include "map/MapHexItemRepository.h"
void UnitTypeEditor::CreateUnit()
{
	if (false == IsUnitTypeEditorInitialzedForCreatingUnit())
	{
		return;
	}

	GameUnitParameterObject gameUnitParameterObject;
	gameUnitParameterObject.GameMapItemId = ActiveGameMapItemId;
	gameUnitParameterObject.ModelUnitTypeObject = ActiveModelUnitType;
	gameUnitParameterObject.ModelOwnerTypeId = ActiveGameOwnerItemId;

	GameUnitItemFactory gameUnitItemFactory;
	GameUnitItem* created = gameUnitItemFactory.CreateGameUnitItemFromScratch(gameUnitParameterObject);

	if (nullptr == created)
	{
		jha::GetLog()->Log_MESSAGE(tr("Unable to create GameUnitItem from type %1!").arg(QString::number(ActiveModelUnitType->GetId())));
		return;
	}

	if (false == TerrainAccessTester::Accessable(ActiveModelUnitType, ActiveGameMapItemId))
	{
		return;
	}

	MapUnitItemFactory mapUnitItemFactory;
	if (false == mapUnitItemFactory.Create(MapViewInstance, created))
	{
		return;
	}
	jha::GetLog()->Log_DEBUG(tr("MapUnitItem (Id=%1) successfully created on HexItem (Id=%2)!").arg(QString::number(created->GetId())).arg(QString::number(ActiveGameMapItemId)));
}

void UnitTypeEditor::SlotDeleteUnitFromGameUnitId(int gameUnitId)
{
	if (false == BaseEditor::GetActive())
	{
		return;
	}

	GameUnitItem* gameUnitItemToDelete = GameUnitItemRepository::GetInstance()->GetGameUnitItemById(gameUnitId);
	if (nullptr == gameUnitItemToDelete)
	{
		return;
	}
	ActiveGameMapItemId = gameUnitItemToDelete->GetGameMapItemId();
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
	return GameUnitItemRepository::GetInstance()->GetGameUnitItemsCountByGameMapItemId(ActiveGameMapItemId);
}

bool UnitTypeEditor::IsSelectedGameMapItemInitialized() const
{
	return VALUE_NOT_INITIALIZED != ActiveGameMapItemId;
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

	if (nullptr == ActiveModelUnitType)
	{
		jha::GetLog()->Log_MESSAGE(tr("Class member <ActiveUnitType> is null! -> SlotActiveUnitTypeId()"));
		return false;
	}

	if (true == HasMapHexItemUnits())
	{
		jha::GetLog()->Log_MESSAGE(tr("HexMapItem %1 already contains a UnitItem").arg(QString::number(ActiveGameMapItemId)));
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
		jha::GetLog()->Log_DEBUG(tr("HexMapItem %1 has no units to delete!").arg(QString::number(ActiveGameMapItemId)));
		return false;  //No unit to delete;
	}

	return true;
}

