#ifndef MAPHEXITEMFACTORY_H
#define MAPHEXITEMFACTORY_H

#include "MapHexItemSetting.h"

class GameMapTile;
class MapView;

class MapHexItemFactory
{
public:
	/** */
	bool Create( MapView* mapView );
private:
	/** */
	bool CreateTopLeftPosition(int col, int row, QPointF &topLeftPosition);
	/** */
	const QImage* GetImage(const GameMapTile* modelMapItem);
private:
	friend class ModelProgramFactory;
	static MapHexItemSetting	MapHexItemSettingObject;
};

#endif // MAPHEXITEMFACTORY_H