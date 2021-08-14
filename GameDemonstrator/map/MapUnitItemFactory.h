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
	bool Create(MapView* mapView);
	/** */
	bool Create(MapView* mapView, const GameUnitItem* gameItemUnit);
	/** */
	bool DeleteUnit(MapView* mapView, int unitItemId);
private:
	/** */
	const QPointF AdjustTopLeftPosition(const QPointF& topLeftPosition);
	/** */
	const QImage* GetImage(const GameUnitItem* gameUnitItem);
};

#endif // MAPVIEWUNITITEMFACTORY_H
