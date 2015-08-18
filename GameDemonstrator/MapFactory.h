#pragma once

class CCreateNewMap;
class MapView;

class CMapFactory
{
public:
	/** */
	CMapFactory();
	/** */
	~CMapFactory();
	/** */
	CCreateNewMap* CreateNewMapAction( QObject *parent, QAction *action, MapView *mapView );
};

