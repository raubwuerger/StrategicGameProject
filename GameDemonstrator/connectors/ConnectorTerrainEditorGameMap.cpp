#include "stdafx.h"
#include "ConnectorTerrainEditorGameMap.h"
#include "..\game\ModelMapRepository.h"
#include "..\model\ModelTerrainTypeRepository.h"
#include "..\model\ModelTerrainType.h"
#include "LogInterface.h"


ConnectorTerrainEditorGameMap::ConnectorTerrainEditorGameMap()
{
}


ConnectorTerrainEditorGameMap::~ConnectorTerrainEditorGameMap()
{
}

void ConnectorTerrainEditorGameMap::SlotTerrainTypeChanged(int modelMapId, int terrainTypeId)
{
	ModelMapItem *modelMapToUpdate = ModelMapRepository::GetInstance()->GetModelMapItemById(modelMapId);
	if( nullptr == modelMapToUpdate )
	{
		jha::GetLog()->Log_DEBUG( tr("ModelMapItem with Id=%1 not found!").arg(QString::number(modelMapId)) );
		return;
	}

	ModelTerrainType* modelTerrainType = ModelTerrainTypeRepository::GetInstance()->FindTerrainTypeById(terrainTypeId);
	if( nullptr == modelTerrainType )
	{
		jha::GetLog()->Log_DEBUG( tr("ModelTerrainType with Id=%1 not found!").arg(QString::number(terrainTypeId)) );
		return;
	}

	modelMapToUpdate->SetModelTerrainType(modelTerrainType);
}
