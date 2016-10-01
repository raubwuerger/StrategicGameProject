#pragma once

class CCreateNewMap;
class CMapView;
class CTerrainType;

/** @stereotype factory*/
class CMapFactory
{
public:
	/** */
	CMapFactory();
	/** */
	~CMapFactory();
	/** */
	CCreateNewMap* CreateNewMapAction( QObject *parent, QAction *action, CMapView *mapView, const CTerrainType *defaultTerrainType );
};

