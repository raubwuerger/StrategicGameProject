#include "stdafx.h"
#include "UnitTypeEditor.h"
#include "model/ModelUnitTypeRepository.h"
#include "model/ModelUnitType.h"
#include "game/GameUnitItemRepository.h"
#include "game/GameUnitItemFactory.h"

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
	if (nullptr == ActiveUnitType)
	{
		return;
	}

	if (true == HasMapHexItemUnits())
	{
		return;
	}

	GameUnitItemFactory gameUnitItemFactory;
	GameUnitItem* created = gameUnitItemFactory.CreateGameUnitItemFromScratch(ActiveUnitType,SelectedGameMapItem);

	return;
	/*
	GameMapItem *mapItemAddingUnit = GameMapItemRepository::GetInstance()->GetGameMapItemById(modelMapId);
	if (nullptr == mapItemAddingUnit)
	{
		jha::GetLog()->Log_DEBUG(tr("ModelMapItem with Id=%1 not found!").arg(QString::number(modelMapId)));
		return;
	}

	const ModelUnitType* modelUnitType = ModelUnitTypeRepository::GetInstance()->FindModelUnitTypeById(unitTypeId);
	if (nullptr == modelUnitType)
	{
		jha::GetLog()->Log_DEBUG(tr("ModelUnitType with Id=%1 not found!").arg(QString::number(unitTypeId)));
		return;
	}
	*/
}

void UnitTypeEditor::DeleteUnit()
{
	//TODO: Check if hexMapItem has a item. If yes remove item
}

bool UnitTypeEditor::HasMapHexItemUnits()
{
	return GameUnitItemRepository::GetInstance()->GetGameMapItemGameUnitItems(SelectedGameMapItem);
}

