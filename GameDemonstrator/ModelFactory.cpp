#include "stdafx.h"
#include "ModelFactory.h"
#include "model/GameMap.h"
#include "model/GameMapConfig.h"

ModelFactory::ModelFactory()
{
}


ModelFactory::~ModelFactory()
{
}

void ModelFactory::CreateEmptyMap(GameMap** gameMap)
{
	*gameMap = new GameMap;
	(*gameMap)->Init( GameMapConfig::GetInstance()->Rows, GameMapConfig::GetInstance()->Cols );
}
