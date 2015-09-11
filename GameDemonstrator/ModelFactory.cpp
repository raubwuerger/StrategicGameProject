#include "stdafx.h"
#include "ModelFactory.h"
#include "model\Map.h"
#include "GameInitialisationData.h"

namespace GDModel
{

CModelFactory::CModelFactory()
{
}


CModelFactory::~CModelFactory()
{
}

void CModelFactory::CreateEmptyMap( const GDModel::CGameInitialisationData& data, CMap* map )
{
 	map = new CMap;
 	map->Init( data.Rows, data.Cols );
}

}