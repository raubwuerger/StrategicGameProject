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
private:
	/** */
	QPolygonF CreateFlatToppedHexagon(double sizeLength) const;
	/** */
	QPointF CreateFlatToppedHexagonCorner(const QPointF& center, double size, unsigned int index) const;
	/** */
	QPolygonF CreatePointyToppedHexagon(double sizeLength) const;
	/** */
	QPointF CreatePointyToppedHexagonCorner(const QPointF& center, double size, unsigned int index) const;
};

#endif // HEXAGONFACTORY_H