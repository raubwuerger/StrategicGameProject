#include "stdafx.h"
#include "ModelFactory.h"
#include "model\Map.h"

namespace GDModel
{

CModelFactory::CModelFactory()
{
}


CModelFactory::~CModelFactory()
{
}

void CModelFactory::CreateEmptyMap( int rows, int cols, CMap* map )
{
	map = new CMap;
	map->Init( rows, cols );
}

}