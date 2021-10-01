#ifndef HEXAGONFACTORY_H
#define HEXAGONFACTORY_H

class HexagonItem;

class HexagonFactory
{
public:
	/** */
	HexagonItem* CreateFlatTopped();
	/** */
	HexagonItem* CreatePointyTopped();
public:
	static const double HEXAGON_DISTANCE_CENTER_CORNER;
private:
	/** */
	QPolygonF CreateFlatToppedHexagon(double sizeLength = 48.0) const;
	/** */
	QPolygonF CreatePointyToppedHexagon(double sizeLength = 48.0) const;
	/** */
	QPointF CreateFlatToppedHexagonCorner(double size, unsigned int index) const;
	/** */
	QPointF CreatePointyToppedHexagonCorner(double size, unsigned int index) const;
};

#endif // HEXAGONFACTORY_H