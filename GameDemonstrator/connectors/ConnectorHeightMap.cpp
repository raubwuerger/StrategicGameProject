#include "stdafx.h"
#include "ConnectorHeightMap.h"

void ConnectorHeightMap::SlotGetGameMapCreatorHeightMapData(GameMapCreatorHeightMapData creationData)
{
	CreationData = creationData;
}

GameMapCreatorHeightMapData ConnectorHeightMap::GetGameMapCreatorHeightMapData() const
{
	return CreationData;
}
