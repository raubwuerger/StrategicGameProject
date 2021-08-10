#include "stdafx.h"
#include "ConnectorUnitTypeGameMap.h"
#include "game\ModelMapItem.h"
#include "game\ModelMapRepository.h"
#include "model\ModelUnitType.h"
#include "model\ModelUnitTypeRepository.h"
#include "LogInterface.h"

ConnectorUnitTypeGameMap::ConnectorUnitTypeGameMap()
{

}

ConnectorUnitTypeGameMap::~ConnectorUnitTypeGameMap()
{

}

void ConnectorUnitTypeGameMap::SlotUnitTypeAdded(int modelMapId, int unitTypeId)
{
	ModelMapItem *mapItemAddingUnit = ModelMapRepository::GetInstance()->GetModelMapItemById(modelMapId);
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

//	mapItemAddingUnit->SetModelTerrainType(ModelUnitType);
}

