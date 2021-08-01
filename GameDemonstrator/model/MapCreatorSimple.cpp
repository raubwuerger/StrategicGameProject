#include "stdafx.h"
#include "MapCreatorSimple.h"
#include "ModelMapRepository.h"
#include "ModelMapConfig.h"
#include "ModelTerrainTypeRepository.h"
#include "ModelMapItem.h"


MapCreatorSimple::MapCreatorSimple()
	: MapItemId(0)
{

}

bool MapCreatorSimple::CreateMap()
{
	MapItemId = 0;
	unsigned int cols = ModelMapConfig::GetInstance()->Cols;
	unsigned int rows = ModelMapConfig::GetInstance()->Rows;

	const ModelTerrainType* defaultTerrainType = ModelTerrainTypeRepository::GetInstance()->GetDefaultTerrainType();

	QVector< QVector<ModelMapItem*> >* theCreatedMap = new QVector< QVector<ModelMapItem*> >();
	theCreatedMap->reserve(rows);
	for( unsigned int currentRow = 0; currentRow < rows; currentRow++ )
	{
		QVector<ModelMapItem*> tempRow;
		tempRow.reserve(cols);
		for( unsigned int currentCol = 0; currentCol < cols; currentCol++ )
		{
			ModelMapItem* modelMapItem = new ModelMapItem(currentRow,currentCol,++MapItemId);
			modelMapItem->SetModelTerrainType( defaultTerrainType );
			tempRow.append( modelMapItem );
		}
		theCreatedMap->append(tempRow);
	}

	ModelMapRepository::GetInstance()->SetMapItems( theCreatedMap );
	return true;
}

ModelMapRepository* MapCreatorSimple::GetMap()
{
	return ModelMapRepository::GetInstance();
}

