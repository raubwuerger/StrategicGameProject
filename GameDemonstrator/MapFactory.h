#pragma once

class CCreateNewMap;
class MapView;
class CTerrainTypeRepository;

/** @stereotype factory*/
class CMapFactory
{
public:
	/** */
	CMapFactory();
	/** */
	~CMapFactory();
	/** */
	CCreateNewMap* CreateNewMapAction( QObject *parent, QAction *action, MapView *mapView, CTerrainTypeRepository *terrainTypeRepository );
};

