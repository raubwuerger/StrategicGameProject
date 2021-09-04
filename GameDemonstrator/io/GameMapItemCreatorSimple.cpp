#include "stdafx.h"
#include "GameMapItemCreatorSimple.h"
#include "game/GameMapItemRepository.h"
#include "model/ModelTerrainTypeRepository.h"
#include "game/GameMapItem.h"
#include "model/ModelProgramFactory.h"
#include "model/ModelProgramSettings.h"
#include "model/ModelTerrainType.h"
#include "gameController/GameConfig.h"

GameMapItemCreatorSimple::GameMapItemCreatorSimple()
	: MapItemId(0)
{

}

bool GameMapItemCreatorSimple::CreateMap()
{
	MapItemId = 0;
	unsigned int cols = GameConfig::MapCols;
	unsigned int rows = GameConfig::MapRows;

	QVector< QVector<GameMapItem*> >* simpleMap = new QVector< QVector<GameMapItem*> >();
	simpleMap->reserve(rows);
	for( unsigned int currentRow = 0; currentRow < rows; currentRow++ )
	{
		QVector<GameMapItem*> tempRow;
		tempRow.reserve(cols);
		for( unsigned int currentCol = 0; currentCol < cols; currentCol++ )
		{
			tempRow.append( CreateGameMapItem(currentRow,currentCol) );
		}
		simpleMap->append(tempRow);
	}

	GameMapItemRepository::GetInstance()->Init();
	GameMapItemRepository::GetInstance()->SetGameMapItems( simpleMap );
	return true;
}

GameMapItem* GameMapItemCreatorSimple::CreateGameMapItem( unsigned int row, unsigned int col )
{
	GameMapItem* modelMapItem = new GameMapItem(row,col,++MapItemId);
	const ModelTerrainType* defaultModelTerrainType = ModelTerrainTypeRepository::GetInstance()->GetDefaultTerrainType();
	Q_ASSERT(defaultModelTerrainType);
	modelMapItem->SetModelTerrainType(defaultModelTerrainType);
	modelMapItem->SetModelTerrainTypeId(defaultModelTerrainType->GetId());
	return modelMapItem;
}

