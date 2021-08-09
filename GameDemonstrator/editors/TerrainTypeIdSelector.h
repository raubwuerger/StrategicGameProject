#ifndef TERRAINTYPEIDSELECTOR_H
#define TERRAINTYPEIDSELECTOR_H

#include "ISelector.h"

class TerrainTypeIdSelector : public QObject, ISelector
{
	Q_OBJECT
public:
	/** */
	TerrainTypeIdSelector( int terrainTypeId );
public slots:
	/** */
	void Trigger();
signals:
	/** */
	void SignalTerrainTypeActive( int terrainTypeId );
private:
	int TerrainTypeId;
};

#endif //TERRAINTYPEIDSELECTOR_H