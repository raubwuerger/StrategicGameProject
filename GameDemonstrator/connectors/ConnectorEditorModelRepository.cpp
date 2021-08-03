#include "stdafx.h"
#include "ConnectorEditorModelRepository.h"
#include "..\model\ModelMapRepository.h"
#include "..\model\ModelTerrainTypeRepository.h"
#include "..\model\ModelTerrainType.h"
#include "LogInterface.h"


ConnectorEditorModelRepository::ConnectorEditorModelRepository()
{
}


ConnectorEditorModelRepository::~ConnectorEditorModelRepository()
{
}

void ConnectorEditorModelRepository::UpdateTerrainType(int modelMapId, int terrainTypeId)
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
