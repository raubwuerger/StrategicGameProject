#ifndef MAPVIEWHEXITEM_H
#define MAPVIEWHEXITEM_H

#include <QGraphicsPolygonItem>

//================================================================================
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
	double sideLength;
	double width;
	double height;
	double side;
	QRectF	boundingRect;
	QPolygonF hexPoints;
};

//================================================================================
class MapViewHexItem : public QGraphicsPolygonItem
{
public:
	/** */
	MapViewHexItem( const HexagonData& data, const QPointF& centerPoint, QGraphicsPolygonItem *parent = 0 );
	/** */
	~MapViewHexItem();
	/** */
	void paint();
	/** */
	QRectF boundingRect() const;
private:
	void CreateHexPolygon( const HexagonData &data );
private:
	HexagonData data;
	int row;
	int col;
	QPointF centerPoint;
};

#endif // MAPVIEWHEXITEM_H
