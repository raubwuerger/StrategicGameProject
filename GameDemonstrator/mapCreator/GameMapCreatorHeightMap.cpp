#include "stdafx.h"
#include "GameMapCreatorHeightMap.h"

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
	return false;
}
