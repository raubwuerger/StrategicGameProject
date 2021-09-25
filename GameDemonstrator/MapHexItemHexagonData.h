#ifndef HEXAGONDATA_H
#define HEXAGONDATA_H

//================================================================================
#include <QGraphicsPolygonItem>
/** Enthält die Koordinatenpunkte des Hexagons */
class MapHexItemHexagonData
{
public:
	/** */
	MapHexItemHexagonData( double sideLength );
	/** */
	void MovePosition( const QPointF& topLeft );
	/** */
	const QPolygonF& GetHexPoints() const { return HexPoints; }
	/** */
	const QRectF&	GetBoundingRect() const { return BoundingRect; }
private:
	static const double DEFAULT_HEXE_SIZE;
	static const double WIDTH_SIDE_MULTIPLICATOR;
	static const double ZERO;
	static const float	ROUND_VALUE;
private:
	/** */
	MapHexItemHexagonData();
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
	double		Width;
	double		Height;
	double		Side;
private:
	friend class ExperimentalClass;
	QRectF		BoundingRect;
	QPolygonF	HexPoints;
	double		SideLength;
};

#endif // HEXAGONDATA_H
