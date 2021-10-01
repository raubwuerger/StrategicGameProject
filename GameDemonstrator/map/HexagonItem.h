#ifndef HEXAGONITEM_H
#define HEXAGONITEM_H

class HexagonItem
{
public:
	/** */
	HexagonItem(const QPolygonF& hexagon);
	/** */
	double GetSideLength() const;
	/** */
	double GetBoundingRectHeight() const;
	/** */
	double GetBoundingRectWidth() const;
	/** */
	QPolygonF GetHexagon() const;
	/** */
	QRectF GetBoundingRect() const;
private:
	friend class HexagonFactory;
	double		SideLength;
	double		BoundingRectHeight;
	double		BoundingRectWidth;
	QRectF		BoundingRect;
	QPointF		CenterPoint;
	QPolygonF	Hexagon;
};

#endif // HEXAGONITEM_H