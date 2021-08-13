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

void UnitTypeEditor::SlotSelectedMapHexItem(int col, int row)
{

//	SelectedGameMapItem = gameMapItemId;
}

