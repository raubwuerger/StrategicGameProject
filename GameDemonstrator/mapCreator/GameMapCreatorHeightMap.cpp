#include "stdafx.h"
#include "GameMapCreatorHeightMap.h"
#include "..\libnoise\noise\noise.h"
#include "..\libnoise\noiseutils.h"

GameMapCreatorHeightMap::GameMapCreatorHeightMap()
{

}

void GameMapCreatorHeightMap::SetMapCreationData(GameMapCreatorHeightMapData mapCreationData)
{
	MapCreationData = mapCreationData;
}

bool GameMapCreatorHeightMap::CreateMap()
{
	MapTileId = 0;
	GameMapCreatorHeightMapData creationData;
	creationData.MapSizeX = 120;
	creationData.MapSizeY = 60;
	creationData.LowerXBound = 6.0;
	creationData.UpperXBound = 10.0;
	creationData.LowerZBound = 1.0;
	creationData.UpperZBound = 5.0;
	creationData.OctaveCount = 6;
	creationData.Frequency = 2.0;
	creationData.Persistence = 0.5;
	return false;
}

bool GameMapCreatorHeightMap::GenerateHeightMap()
{
	return false;
}
