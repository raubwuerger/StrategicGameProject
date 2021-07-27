#include "stdafx.h"
#include "ModelFactory.h"
#include "model\GameMap.h"
#include "GameInitialisationData.h"

ModelFactory::ModelFactory()
{
}


ModelFactory::~ModelFactory()
{
}

void ModelFactory::CreateEmptyMap( const GameInitialisationData& data, GameMap** gameMap )
{
 	*gameMap = new GameMap;
 	(*gameMap)->Init( data.Rows, data.Cols );
}
