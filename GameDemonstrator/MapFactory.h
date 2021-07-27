#pragma once

class CreateNewMap;
class MapView;
class TerrainType;

/** @stereotype factory*/
class MapFactory
{
public:
	/** */
	static MapFactory* GetInstance();
	/** */
	void SetMapView( MapView* mapView );
	/** */
	void SetParent( QObject *parent );
	/** */
	CreateNewMap* CreateNewMapFunction();
private:
	/** */
	MapFactory();
	/** */
	~MapFactory();
	/** */
	CreateNewMap* CreateNewMapAction( QObject *parent, QAction *action, MapView *mapView, const TerrainType *defaultTerrainType );
private:
	static MapFactory* Instance;
	CreateNewMap* TheCreateNewMap;
	MapView		*MapViewInstance;
	QObject		*Parent;
};

