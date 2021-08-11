#ifndef MAPHEXITEMFACTORY_H
#define MAPHEXITEMFACTORY_H

class GameMapItem;
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
	const QImage* GetImage(const GameMapItem* modelMapItem);
};

#endif // MAPHEXITEMFACTORY_H