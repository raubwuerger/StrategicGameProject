#include "stdafx.h"
#include "TerrainTypeFactory.h"
#include <QDomNode>

CTerrainTypeFactory::CTerrainTypeFactory()
{
}

CTerrainTypeFactory::~CTerrainTypeFactory()
{
}

CTerrainType* CTerrainTypeFactory::CreateTerrainTypeFromXML( const QDomNode& node )
{
	return nullptr;
}
