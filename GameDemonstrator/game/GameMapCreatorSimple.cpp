#include "stdafx.h"
#include "GameMapCreatorSimple.h"
#include "GameMapRepository.h"
#include "model/ModelTerrainTypeRepository.h"
#include "GameMapItem.h"
#include "model/ModelProgramFactory.h"
#include "model/ModelProgramSettings.h"

GameMapCreatorSimple::GameMapCreatorSimple()
	: MapItemId(0)
{

}

bool GameMapCreatorSimple::CreateMap()
{
	MapItemId = 0;
	unsigned int cols = ModelProgramFactory::ModelProgramSettingsInstance->DebugCols;
	unsigned int rows = ModelProgramFactory::ModelProgramSettingsInstance->DebugRows;

	QVector< QVector<GameMapItem*> >* simpleMap = new QVector< QVector<GameMapItem*> >();
	simpleMap->reserve(rows);
	for( unsigned int currentRow = 0; currentRow < rows; currentRow++ )
	{
		QVector<GameMapItem*> tempRow;
		tempRow.reserve(cols);
		for( unsigned int currentCol = 0; currentCol < cols; currentCol++ )
		{
			tempRow.append( CreateModelMapItem(currentRow,currentCol) );
		}
		simpleMap->append(tempRow);
	}

	GameMapRepository::GetInstance()->Init();
	GameMapRepository::GetInstance()->SetGameMapItems( simpleMap );
	return true;
}

GameMapRepository* GameMapCreatorSimple::GetMap()
{
	return GameMapRepository::GetInstance();
}

GameMapItem* GameMapCreatorSimple::CreateModelMapItem( unsigned int row, unsigned int col )
{
	GameMapItem* modelMapItem = new GameMapItem(row,col,++MapItemId);
	modelMapItem->SetModelTerrainType( ModelTerrainTypeRepository::GetInstance()->GetDefaultTerrainType() );
	return modelMapItem;
}

