#include "stdafx.h"
#include "MapFactory.h"
#include "CreateNewMap.h"
#include "QObject.h"

MapFactory::MapFactory()
{
}

MapFactory::~MapFactory()
{
}

CreateNewMap* MapFactory::CreateNewMapAction( QObject *parent, QAction *action, MapView *mapView, const TerrainType *defaultTerrainType )
{
	CreateNewMap *newMapCreator = new CreateNewMap(parent);
	newMapCreator->MapView = mapView;
	newMapCreator->DefaultTerrainType = defaultTerrainType;
	QObject::connect(action, SIGNAL(triggered()), newMapCreator, SLOT(DoCreateNewMap()), Qt::QueuedConnection );
	QObject::connect(action, SIGNAL(triggered()), newMapCreator, SLOT(DoCreateNewMapStatic()), Qt::QueuedConnection );

	return newMapCreator;
}
