#include "stdafx.h"
#include "ModelFactory.h"
#include "model\GameMap.h"
#include "GameInitialisationData.h"

namespace GDModel
{

CModelFactory::CModelFactory()
{
}


CModelFactory::~CModelFactory()
{
}

void CModelFactory::CreateEmptyMap( const CGameInitialisationData& data, GameMap** gameMap )
{
 	*gameMap = new GameMap;
 	(*gameMap)->Init( data.Rows, data.Cols );
}

}