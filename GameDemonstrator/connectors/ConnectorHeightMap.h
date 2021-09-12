#ifndef CONNECTORHEIGHTMAP_H
#define CONNECTORHEIGHTMAP_H

#include "mapCreator/GameMapCreatorHeightMapData.h"

class ConnectorHeightMap : public QObject
{
	Q_OBJECT
public:
	/** */
	void SlotGetGameMapCreatorHeightMapData(GameMapCreatorHeightMapData creationData);
	/** */
	GameMapCreatorHeightMapData GetGameMapCreatorHeightMapData() const;
private:
	GameMapCreatorHeightMapData CreationData;
};

#endif // CONNECTORHEIGHTMAP_H