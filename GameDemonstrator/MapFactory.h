#pragma once

class CCreateNewMap;
class MapView;
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
	CCreateNewMap* CreateNewMapAction( QObject *parent, QAction *action, MapView *mapView, const CTerrainType *defaultTerrainType );
};

