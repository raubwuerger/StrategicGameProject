#include "stdafx.h"
#include "UnitTypeEditor.h"
#include "model/ModelUnitTypeRepository.h"
#include "model/ModelUnitType.h"

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
	Q_ASSERT(MapEventManagerInstance);
	const ModelUnitType* foundModelUnitType = ModelUnitTypeRepository::GetInstance()->FindModelUnitTypeById(unitTypeId);
	if (nullptr == foundModelUnitType)
	{
		return;
	}
	//TODO: Die aktuellen MapCoordinaten ermitteln
	//TODO: emit AddUnit(mapId, unitId)
}

void UnitTypeEditor::SlotSelectedMapHexItem(int mapHexItemId)
{
	SelectedGameMapItem = mapHexItemId;
}

void UnitTypeEditor::CreateNewUnit()
{
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

}

