#ifndef HEXAGONITEM_H
#define HEXAGONITEM_H

class HexagonItem
{
public:
	/** */
	HexagonItem(const QPolygonF& hexagon);
private:
	friend class HexagonFactory;
	double		SideLength;
	QPolygonF	Hexagon;
};

#endif // HEXAGONITEM_H