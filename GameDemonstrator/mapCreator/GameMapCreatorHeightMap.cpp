#include "stdafx.h"
#include "GameMapCreatorHeightMap.h"
#include "..\libnoise\noise\noise.h"
#include "..\libnoise\noiseutils.h"

GameMapCreatorHeightMap::GameMapCreatorHeightMap()
{
	GenerateDefaultMapCreationData();
}

void GameMapCreatorHeightMap::SetMapCreationData(GameMapCreatorHeightMapData mapCreationData)
{
	MapCreationData = mapCreationData;
}

bool GameMapCreatorHeightMap::CreateMap()
{
	MapTileId = 0;

	module::Perlin myModule;
	myModule.SetOctaveCount(MapCreationData.OctaveCount);
	myModule.SetFrequency(MapCreationData.Frequency);
	myModule.SetPersistence(MapCreationData.Persistence);
	utils::NoiseMap heightMap;
	utils::NoiseMapBuilderPlane heightMapBuilder;
	heightMapBuilder.SetSourceModule(myModule);
	heightMapBuilder.SetDestNoiseMap(heightMap);
	heightMapBuilder.SetDestSize(MapCreationData.MapSizeX, MapCreationData.MapSizeY);
	heightMapBuilder.SetBounds(MapCreationData.LowerXBound, MapCreationData.UpperXBound, MapCreationData.LowerZBound, MapCreationData.UpperZBound);
	heightMapBuilder.Build();

	return false;
}

bool GameMapCreatorHeightMap::GenerateHeightMap()
{
	return false;
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
