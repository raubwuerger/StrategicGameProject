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
class HexItemEventManager : public QObject
{
	Q_OBJECT
public:
	HexItemEventManager() {}
signals:
	void HexItemEntered( int row, int col );
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
	/** */
	virtual void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
	/** */
	virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);
	/** Set eventItem */
	void SetHexItemEventManager( HexItemEventManager * val) { eventItem = val; }
	/** Get row */
	 int GetRow() const { return row; }
	/** Set row */
	void SetRow(  int val) { row = val; }
	/** Get col */
	int GetCol() const { return col; }
	/** Set col */
	void SetCol(  int val) { col = val; }
private:
	/** */
	void CreateHexPolygon( const HexagonData &data );
	/** */
	void ShowSelected();
	/** */
	void ShowOriginal();
private:
	HexagonData data;
	QPointF centerPoint;
	HexItemEventManager	*eventItem;
	int row;
	int col;
};

#endif // MAPVIEWHEXITEM_H
