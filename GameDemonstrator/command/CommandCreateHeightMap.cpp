#include "stdafx.h"
#include "CommandCreateHeightMap.h"
#include "mapCreator\GameMapCreatorHeightMap.h"
#include "map\MapHexItemFactory.h"

void CommandCreateHeightMap::CreateHeightMap(GameMapCreatorHeightMapData creationData, MapView* mapView)
{
	GameMapCreatorHeightMap mapCreator;
	if (false == mapCreator.CreateMap(creationData))
	{
		Q_ASSERT(false);
		return;
	}

	MapHexItemFactory mapHexItemFactory;
	if (false == mapHexItemFactory.Create(mapView))
	{
		Q_ASSERT(false);
		return;
	}
}
