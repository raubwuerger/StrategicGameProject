#pragma once

class CreateNewMap;
class MapView;
class TerrainType;

/** @stereotype factory*/
class MapFactory
{
public:
	/** */
	MapFactory();
	/** */
	~MapFactory();
	/** */
	CreateNewMap* CreateNewMapAction( QObject *parent, QAction *action, MapView *mapView, const TerrainType *defaultTerrainType );
};

