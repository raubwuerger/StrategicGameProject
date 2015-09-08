#include "stdafx.h"
#include "GameFactory.h"
#include "GameInitialisationData.h"
#include "model\Map.h"

CGameFactory::CGameFactory()
{
}

CGameFactory::~CGameFactory()
{
}

void CGameFactory::CreateNewGame( const CGameInitialisationData& data )
{

}

#include "ModelFactory.h"
void CGameFactory::CreateModel( const CGameInitialisationData& data )
{
	GDModel::CModelFactory modelFactory;

	GDModel::CMap map;
	modelFactory.CreateEmptyMap( data.Rows, data.Cols, &map );
}

