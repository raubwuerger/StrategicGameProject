#include "stdafx.h"
#include "TerrainTypeIdSelector.h"

TerrainTypeIdSelector::TerrainTypeIdSelector( int terrainTypeId ) 
	: TerrainTypeId(terrainTypeId)
{

}

void TerrainTypeIdSelector::SlotTrigger()
{
	emit SignalTerrainTypeActive(TerrainTypeId);
}


