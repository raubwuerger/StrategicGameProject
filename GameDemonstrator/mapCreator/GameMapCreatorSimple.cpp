#include "stdafx.h"
#include "GameMapCreatorSimple.h"
#include "game/GameMapTileRepository.h"
#include "model/ModelTerrainTypeRepository.h"
#include "game/GameMapTile.h"
#include "model/ModelProgramFactory.h"
#include "model/ModelProgramSettings.h"
#include "model/ModelTerrainType.h"
#include "game/GameConfig.h"

GameMapCreatorSimple::GameMapCreatorSimple()
	: MapItemId(0)
{

}

bool GameMapCreatorSimple::CreateMap()
{
	MapItemId = 0;
	unsigned int cols = GameConfig::MapCols;
	unsigned int rows = GameConfig::MapRows;

	QVector< QVector<GameMapTile*> >* simpleMap = new QVector< QVector<GameMapTile*> >();
	simpleMap->reserve(rows);
	for( unsigned int currentRow = 0; currentRow < rows; currentRow++ )
	{
		QVector<GameMapTile*> tempRow;
		tempRow.reserve(cols);
		for( unsigned int currentCol = 0; currentCol < cols; currentCol++ )
		{
			tempRow.append( CreateGameMapItem(currentRow,currentCol) );
		}
		simpleMap->append(tempRow);
	}

	GameMapTileRepository::GetInstance()->Init();
	GameMapTileRepository::GetInstance()->SetGameMapTiles( simpleMap );
	return true;
}

GameMapTile* GameMapCreatorSimple::CreateGameMapItem( unsigned int row, unsigned int col )
{
	GameMapTile* modelMapItem = new GameMapTile(row,col,++MapItemId);
	const ModelTerrainType* defaultModelTerrainType = ModelTerrainTypeRepository::GetInstance()->GetDefaultTerrainType();
	Q_ASSERT(defaultModelTerrainType);
	modelMapItem->SetModelTerrainType(defaultModelTerrainType);
	modelMapItem->SetModelTerrainTypeId(defaultModelTerrainType->GetId());
	return modelMapItem;
}

