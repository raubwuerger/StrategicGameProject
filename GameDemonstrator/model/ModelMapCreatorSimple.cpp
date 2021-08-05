#include "stdafx.h"
#include "ModelMapCreatorSimple.h"
#include "ModelMapRepository.h"
#include "ModelTerrainTypeRepository.h"
#include "ModelMapItem.h"
#include "ModelProgramFactory.h"
#include "ModelProgramSettings.h"

ModelMapCreatorSimple::ModelMapCreatorSimple()
	: MapItemId(0)
{

}

bool ModelMapCreatorSimple::CreateMap()
{
	MapItemId = 0;
	unsigned int cols = ModelProgramFactory::GetInstance()->GetConfig()->DebugCols;
	unsigned int rows = ModelProgramFactory::GetInstance()->GetConfig()->DebugRows;

	QVector< QVector<ModelMapItem*> >* simpleMap = new QVector< QVector<ModelMapItem*> >();
	simpleMap->reserve(rows);
	for( unsigned int currentRow = 0; currentRow < rows; currentRow++ )
	{
		QVector<ModelMapItem*> tempRow;
		tempRow.reserve(cols);
		for( unsigned int currentCol = 0; currentCol < cols; currentCol++ )
		{
			tempRow.append( CreateModelMapItem(currentRow,currentCol) );
		}
		simpleMap->append(tempRow);
	}

	ModelMapRepository::GetInstance()->SetModelMapItems( simpleMap );
	return true;
}

ModelMapRepository* ModelMapCreatorSimple::GetMap()
{
	return ModelMapRepository::GetInstance();
}

ModelMapItem* ModelMapCreatorSimple::CreateModelMapItem( unsigned int row, unsigned int col )
{
	ModelMapItem* modelMapItem = new ModelMapItem(row,col,++MapItemId);
	modelMapItem->SetModelTerrainType( ModelTerrainTypeRepository::GetInstance()->GetDefaultTerrainType() );
	return modelMapItem;
}

