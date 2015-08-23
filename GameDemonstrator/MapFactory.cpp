#include "stdafx.h"
#include "MapFactory.h"
#include "CreateNewMap.h"
#include "QObject.h"

CMapFactory::CMapFactory()
{
}

CMapFactory::~CMapFactory()
{
}

CCreateNewMap* CMapFactory::CreateNewMapAction( QObject *parent, QAction *action, MapView *mapView, CTerrainTypeRepository *terrainTypeRepository )
{
	CCreateNewMap *newMapCreator = new CCreateNewMap(parent);
	newMapCreator->m_MapView = mapView;
	newMapCreator->m_TerrainTypeRepository = terrainTypeRepository;
	QObject::connect(action, SIGNAL(triggered()), newMapCreator, SLOT(DoCreateNewMap()), Qt::QueuedConnection );

	return newMapCreator;
}
