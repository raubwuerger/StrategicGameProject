#include "stdafx.h"
#include "UnitTypeEditor.h"
#include "model/ModelUnitTypeRepository.h"
#include "model/ModelUnitType.h"
#include "game/GameUnitItemRepository.h"
#include "game/GameUnitItemFactory.h"
#include "map/MapUnitItemFactory.h"
#include "LogInterface.h"

UnitTypeEditor::UnitTypeEditor(QObject *parent)
	: ActiveUnitType(nullptr),
	SelectedGameMapItem(-1)
{

}

UnitTypeEditor::~UnitTypeEditor()
{

}

void UnitTypeEditor::SetMapEventManager(MapHexItemEventManager* mapEventManager)
{
	MapEventManagerInstance = mapEventManager;
}

void UnitTypeEditor::SetMapView(MapView* mapView)
{
	MapViewInstance = mapView;
}

void UnitTypeEditor::SlotActiveUnitTypeId(int unitTypeId)
{
	ActiveUnitType = ModelUnitTypeRepository::GetInstance()->FindModelUnitTypeById(unitTypeId);
}

void UnitTypeEditor::SlotDeleteUnit(int mapHexItemId)
{
	SelectedGameMapItem = mapHexItemId;
	DeleteUnit();
}

void UnitTypeEditor::SlotAddUnit(int mapHexItemId)
{
	SelectedGameMapItem = mapHexItemId;
	CreateUnit();
}

void UnitTypeEditor::CreateUnit()
{
	if (nullptr == MapViewInstance)
	{
		jha::GetLog()->Log_MESSAGE(tr("Class member <MapViewInstance> is null! -> SetMapView()"));
		return;
	}

	if (nullptr == ActiveUnitType)
	{
		jha::GetLog()->Log_MESSAGE(tr("Class member <ActiveUnitType> is null! -> SlotActiveUnitTypeId()"));
		return;
	}

	if (-1 == SelectedGameMapItem)
	{
		jha::GetLog()->Log_MESSAGE(tr("Class member <SelectedGameMapItem> is not initialized! -> SlotAddUnit()"));
		return;
	}

	if (true == HasMapHexItemUnits())
	{
		jha::GetLog()->Log_MESSAGE(tr("HexMapItem %1 already contains a UnitItem").arg(QString::number(SelectedGameMapItem)));
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
	if (false == mapUnitItemFactory.CreateUnit(MapViewInstance, created))
	{
		return;
	}
	return;
}

void UnitTypeEditor::DeleteUnit()
{
	//TODO: Check if hexMapItem has a item. If yes remove item
}

bool UnitTypeEditor::HasMapHexItemUnits()
{
	return GameUnitItemRepository::GetInstance()->GetGameMapItemGameUnitItems(SelectedGameMapItem);
}

