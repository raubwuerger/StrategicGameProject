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

CCreateNewMap* CMapFactory::CreateNewMapAction( QObject *parent, QAction *action, MapView *mapView )
{
	CCreateNewMap *newMapCreator = new CCreateNewMap(parent);
	newMapCreator->m_MapView = mapView;
	QObject::connect(action, SIGNAL(triggered()), newMapCreator, SLOT(DoCreateNewMap()), Qt::QueuedConnection );

	return newMapCreator;
}
