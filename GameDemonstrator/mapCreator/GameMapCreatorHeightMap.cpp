#include "stdafx.h"
#include "GameMapCreatorHeightMap.h"
#include "game\GameMapTile.h"
#include "game\GameMapTileRepository.h"
#include "helper\HeightMapGenerator.h"
#include "model\ModelTerrainTypeRepository.h"


GameMapCreatorHeightMap::GameMapCreatorHeightMap()
{
	GenerateDefaultMapCreationData();
}

void GameMapCreatorHeightMap::GenerateDefaultMapCreationData()
{
	MapCreationData.MapSizeX = 120;
	MapCreationData.MapSizeY = 60;
	MapCreationData.LowerXBound = 6.0;
	MapCreationData.UpperXBound = 10.0;
	MapCreationData.LowerZBound = 1.0;
	MapCreationData.UpperZBound = 5.0;
	MapCreationData.OctaveCount = 6;
	MapCreationData.Frequency = 2.0;
	MapCreationData.Persistence = 0.5;
}

void GameMapCreatorHeightMap::SetMapCreationData(GameMapCreatorHeightMapData mapCreationData)
{
	MapCreationData = mapCreationData;
}

bool GameMapCreatorHeightMap::CreateMap(GameMapCreatorHeightMapData mapCreationData)
{
	MapCreationData = mapCreationData;
	return CreateMap();
}

bool GameMapCreatorHeightMap::CreateMap()
{
	MapTileId = 0;

	std::vector< std::vector<float> > heightMapVector;
	if (false == GenerateHeightMap(heightMapVector))
	{
		return false;
	}

	return CreateGameMapTiles(heightMapVector);
}

bool GameMapCreatorHeightMap::GenerateHeightMap(std::vector< std::vector<float> >& heightMapVector)
{
	HeightMapGenerator heightMapGenerator;
	return heightMapGenerator.GenerateHeightMap(MapCreationData, heightMapVector);
}

bool GameMapCreatorHeightMap::CreateGameMapTiles(std::vector< std::vector<float> >& heightMapVector)
{
	if (true == heightMapVector.empty())
	{
		return false; //TODO: no items!!!
	}

	int rows = heightMapVector.size();
	int cols = heightMapVector[0].size();

	QVector< QVector<GameMapTile*> >* gameMap = new QVector< QVector<GameMapTile*> >();
	gameMap->reserve(rows);
	
	for (unsigned int currentRow = 0; currentRow < rows; currentRow++)
	{
		QVector<GameMapTile*> tempRow;
		tempRow.reserve(cols);
		for (unsigned int currentCol = 0; currentCol < cols; currentCol++)
		{
			GameMapTile* gameMapTile = CreateGameMapTile(currentRow, currentCol);
			const ModelTerrainType* modelTerrainType = GetModelTerrainType(heightMapVector[currentRow][currentCol]);
			gameMapTile->SetModelTerrainType(modelTerrainType);
			tempRow.append(gameMapTile);
		}
		gameMap->append(tempRow);
	}
	
	GameMapTileRepository::GetInstance()->Init();
	GameMapTileRepository::GetInstance()->SetGameMapTiles(gameMap);
	return true;
}

GameMapTile* GameMapCreatorHeightMap::CreateGameMapTile(unsigned int row, unsigned int col)
{
	GameMapTile* gameMapTile = new GameMapTile(row, col, ++MapTileId);
	return gameMapTile;
}

const ModelTerrainType* GameMapCreatorHeightMap::GetModelTerrainType(float value) const
{
	if (value <= -0.2500)
	{
		return ModelTerrainTypeRepository::GetInstance()->GetById(3); //Ocean
	}
	if (value <= 0.0000 && value > -0.2500)
	{
		return ModelTerrainTypeRepository::GetInstance()->GetById(1); //Plain
	}
	if (value <= 0.0625 && value > 0.0000)
	{
		return ModelTerrainTypeRepository::GetInstance()->GetById(2); //wood
	}
	if (value <= 0.1250 && value > 0.0625)
	{
		return ModelTerrainTypeRepository::GetInstance()->GetById(4); //hill
	}
	return ModelTerrainTypeRepository::GetInstance()->GetById(5); //mountain
}
