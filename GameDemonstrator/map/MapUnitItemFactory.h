#ifndef MAPVIEWUNITITEMFACTORY_H
#define MAPVIEWUNITITEMFACTORY_H

class GameUnit;
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
	bool Create(MapView* mapView, const GameUnit* gameItemUnit);
	/** */
	bool DeleteUnit(MapView* mapView, int unitItemId);
private:
	/** */
	const QPointF AdjustTopLeftPosition(const QPointF& topLeftPosition);
	/** */
	const QImage* GetImage(const GameUnit* gameUnitItem);
public:
	static QPointF MAPHEXITEM_OFFSET;
private:
	int		DefaultBorderWidth;
	int		DefaultBorderWidthSelected;
};

#endif // MAPVIEWUNITITEMFACTORY_H
