#include "stdafx.h"
#include "GameMapCreatorHeightMap.h"
#include "game\GameMapTile.h"
#include "game\GameMapTileRepository.h"
#include "helper\HeightMapGenerator.h"
#include "helper\MapToVectorSorter.h"
#include "model\ModelTerrainTypeRepository.h"
#include "helper\HeightMapPercentageSplitter.h"
#include "helper\MapToVectorSorter.h"


GameMapCreatorHeightMap::GameMapCreatorHeightMap()
{
	GenerateDefaultMapCreationData();
	DefaultInitHeightValueUpperBorders();
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

	std::vector<float> sorted = MapToVectorSorter::TransformAndSort(heightMapVector);


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
	if (value <= HeightValueUpperBorderOcean)
	{
		return ModelTerrainTypeRepository::GetInstance()->GetById(3); //Ocean
	}
	if (value <= HeightValueUpperBorderPlain && value > HeightValueUpperBorderOcean)
	{
		return ModelTerrainTypeRepository::GetInstance()->GetById(1); //Plain
	}
	if (value <= HeightValueUpperBorderWood && value > HeightValueUpperBorderPlain)
	{
		return ModelTerrainTypeRepository::GetInstance()->GetById(2); //wood
	}
	if (value <= HeightValueUpperBorderHill && value > HeightValueUpperBorderWood)
	{
		return ModelTerrainTypeRepository::GetInstance()->GetById(4); //hill
	}
	return ModelTerrainTypeRepository::GetInstance()->GetById(5); //mountain
}

void GameMapCreatorHeightMap::InitHeightValueUpperBorders(std::vector< std::vector<float> >& heightMapVector)
{
	int percentageOcean = 40;	//40% Ocean
	int percentagePlain = 70;	//30% Plain
	int percentageWood = 88;	//18% Wood
	int percentageHill = 95;	//7% Hill
								// 5% Mountain
//Ergibt sich aus 100% - percentageHill;
//	int percentageOcean = 100;

	HeightMapPercentageSplitter heightMapPercentageSplitter;
	heightMapPercentageSplitter.RegisterPercentageValue(percentageOcean);
	heightMapPercentageSplitter.RegisterPercentageValue(percentagePlain);
	heightMapPercentageSplitter.RegisterPercentageValue(percentageWood);
	heightMapPercentageSplitter.RegisterPercentageValue(percentageHill);

	std::map<int, std::vector<float> > heightMapPercentageValues = heightMapPercentageSplitter.CalculatePercentageValue(MapToVectorSorter::TransformAndSort(heightMapVector));
	if (heightMapPercentageValues.size() != 5)
	{
		return;
	}

	SetPercentageValue(heightMapPercentageValues[0], HeightValueUpperBorderOcean);
	SetPercentageValue(heightMapPercentageValues[1], HeightValueUpperBorderPlain);
	SetPercentageValue(heightMapPercentageValues[2], HeightValueUpperBorderWood);
	SetPercentageValue(heightMapPercentageValues[3], HeightValueUpperBorderHill);
	SetPercentageValue(heightMapPercentageValues[4], HeightValueUpperBorderMountain);
}

void GameMapCreatorHeightMap::DefaultInitHeightValueUpperBorders()
{
	HeightValueUpperBorderOcean = -0.2500;
	HeightValueUpperBorderPlain = 0.0000;
	HeightValueUpperBorderWood = 0.0625;
	HeightValueUpperBorderHill = 0.1250;
	HeightValueUpperBorderMountain = 5.000;
}

void GameMapCreatorHeightMap::SetPercentageValue(const std::vector<float>& values, float& upperPercentageValue)
{

}
