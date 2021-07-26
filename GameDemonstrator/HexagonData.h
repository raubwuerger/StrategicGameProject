#ifndef HEXAGONDATA_H
#define HEXAGONDATA_H

//================================================================================
#include <QGraphicsPolygonItem>
/** Enthält die Koordinatenpunkte des Hexagons */
class HexagonData
{
public:
	/** */
	HexagonData( double sideLength );
	/** */
	void MovePosition( const QPointF& topLeft );
private:
	/** */
	HexagonData();
	/** */
	void calcBoundingRect();
	/** */
	void calcWidth();
	/** */
	void calcHeight();
	/** */
	void calcSide();
	/** */
	void calcHexPointsOrigin();
public:
	double SideLength;
	double Width;
	double Height;
	double Side;
	QRectF	BoundingRect;
	QPolygonF HexPoints;
};

#endif // HEXAGONDATA_H
