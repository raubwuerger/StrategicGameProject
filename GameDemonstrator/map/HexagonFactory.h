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
	/** */
	QPolygonF CreateFlatToppedHexagon(double sizeLength = 48.0) const;
	/** */
	QPolygonF CreatePointyToppedHexagon(double sizeLength = 48.0) const;
public:
	static const double HEXAGON_DISTANCE_CENTER_CORNER;
private:
	/** */
	QPointF CreateFlatToppedHexagonCorner(const QPointF& center, double size, unsigned int index) const;
	/** */
	QPointF CreatePointyToppedHexagonCorner(const QPointF& center, double size, unsigned int index) const;
};

#endif // HEXAGONFACTORY_H