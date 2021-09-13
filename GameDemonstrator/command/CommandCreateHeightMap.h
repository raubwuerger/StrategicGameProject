#ifndef COMMANDCREATEHEIGHTMAP_H
#define COMMANDCREATEHEIGHTMAP_H

#include <QObject>
#include "mapCreator/GameMapCreatorHeightMapData.h"

class MapView;

class CommandCreateHeightMap : public QObject
{
	Q_OBJECT
public:
	/** */
	void CreateHeightMap(GameMapCreatorHeightMapData creationData, MapView* mapView );
};

#endif // COMMANDCREATEHEIGHTMAP_H