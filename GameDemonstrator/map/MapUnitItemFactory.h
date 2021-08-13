#ifndef MAPVIEWUNITITEMFACTORY_H
#define MAPVIEWUNITITEMFACTORY_H

class GameUnitItem;
class MapView;

/** Creates game map representation */
class MapUnitItemFactory
{
public:
	/** */
	MapUnitItemFactory();
	/** */
	~MapUnitItemFactory();
	/** */
	bool CreateUnit(MapView* mapView);
	/** */
	bool CreateUnit(MapView* mapView, int unitItemId, int gameMapItemId);
	/** */
	bool DeleteUnit(MapView* mapView, int unitItemId);
private:
	/** */
	const QPointF AdjustTopLeftPosition(const QPointF& topLeftPosition);
	/** */
	const QImage* GetImage(const GameUnitItem* gameUnitItem);
};

#endif // MAPVIEWUNITITEMFACTORY_H
