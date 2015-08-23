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
	MapViewHexItem( const HexagonData& data, const QPointF& topLeft, QGraphicsPolygonItem *parent = 0 );
	/** */
	~MapViewHexItem();
	/** */
	QRectF boundingRect() const;
	/** */
	virtual void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
	/** */
	virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);
	/** Set eventItem */
	void SetHexItemEventManager( HexItemEventManager * val) { eventItem = val; }
	/** */
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	/** Get row */
	 int GetRow() const { return row; }
	/** Set row */
	void SetRowAndCol( int row, int col );
	/** Get col */
	int GetCol() const { return col; }
	/** Set m_TerrainImage */
	void SetTerrainImage( const QImage *& val) { m_TerrainImage = val; }
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
	QPointF topLeft;
	HexItemEventManager	*eventItem;
	int row;
	int col;
	QString	stringRowCol;
	const QImage	*m_TerrainImage;
};

#endif // MAPVIEWHEXITEM_H
