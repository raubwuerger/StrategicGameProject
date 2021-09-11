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
{

}

bool GameMapCreatorSimple::CreateMap()
{
	MapTileId = 0;
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
			tempRow.append( CreateGameMapTile(currentRow,currentCol) );
		}
		simpleMap->append(tempRow);
	}

	GameMapTileRepository::GetInstance()->Init();
	GameMapTileRepository::GetInstance()->SetGameMapTiles( simpleMap );
	return true;
}

GameMapTile* GameMapCreatorSimple::CreateGameMapTile( unsigned int row, unsigned int col )
{
	GameMapTile* gameMapTile = new GameMapTile(row, col, ++MapTileId);
	const ModelTerrainType* defaultModelTerrainType = ModelTerrainTypeRepository::GetInstance()->GetDefaultTerrainType();
	Q_ASSERT(defaultModelTerrainType);
	gameMapTile->SetModelTerrainType(defaultModelTerrainType);
	gameMapTile->SetModelTerrainTypeId(defaultModelTerrainType->GetId());
	return gameMapTile;
}

