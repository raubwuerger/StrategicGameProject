#include "stdafx.h"
#include "ModelFactory.h"
#include "model\GameMap.h"
#include "GameInitialisationData.h"
#include "model/GameMapConfig.h"

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

void ModelFactory::CreateEmptyMap(GameMap** gameMap)
{
	*gameMap = new GameMap;
	(*gameMap)->Init( GameMapConfig::GetInstance()->Rows, GameMapConfig::GetInstance()->Cols );
}
