#include "stdafx.h"
#include "MapViewHexItem.h"

/************************************************************************/
/* MapViewHexItemData                                                   */
/************************************************************************/
HexagonData::HexagonData( double sideLength )
	: sideLength(sideLength),
	width(0.0),
	height(0.0),
	side(0.0)
{
	calcWidth();
	calcHeight();
	calcSide();
	calcBoundingRect();
	calcHexPointsOrigin();
}

void HexagonData::calcWidth()
{
	width = 2.0 * sideLength;
}

void HexagonData::calcHeight()
{
	height = sqrt(3) * sideLength;
}

void HexagonData::calcSide()
{
	side = 3.0 / 2.0 * sideLength;
}

void HexagonData::calcBoundingRect()
{
	boundingRect = QRectF(QPointF(-width,-height),QSizeF(width, height));
}

void HexagonData::calcHexPointsOrigin()
{
	hexPoints << QPointF(0,height*0.5) 
		<< QPointF(width - side,0.0) 
		<< QPointF(side,0.0) 
		<< QPointF(width,height*0.5) 
		<< QPointF(side,height) 
		<< QPointF(width - side,height);
}

void HexagonData::MovePosition( const QPointF& topLeft )
{
	boundingRect.moveTopLeft( topLeft );
	hexPoints.translate( topLeft );
}

/************************************************************************/
/* MapViewHexItem                                                       */
/************************************************************************/
MapViewHexItem::MapViewHexItem( const HexagonData& data, const QPointF& centerPoint, QGraphicsPolygonItem *parent /*= 0*/ )
	: data(data),
	centerPoint(centerPoint),
	col(-1),
	row(-1)
{
	this->data.MovePosition(centerPoint);
	CreateHexPolygon(this->data);
	setAcceptHoverEvents(true);
	setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton );
}

MapViewHexItem::~MapViewHexItem()
{

}

void MapViewHexItem::paint()
{
// 	int grass = 20;
// 	setPen(QPen(Qt::black, 0));
// 	setBrush(QBrush(QColor(255-grass,255,255-grass)));
	update(boundingRect());
}

QRectF MapViewHexItem::boundingRect() const
{
	return data.boundingRect;
}

void MapViewHexItem::CreateHexPolygon( const HexagonData &data )
{
	setPolygon(data.hexPoints);
	setFlags(QGraphicsItem::ItemIsFocusable);
}

void MapViewHexItem::hoverEnterEvent(QGraphicsSceneHoverEvent * event) 
{
	ShowSelected();
	QGraphicsPolygonItem::hoverEnterEvent(event);
	event->ignore();
}

void MapViewHexItem::hoverLeaveEvent(QGraphicsSceneHoverEvent * event) 
{
	ShowOriginal();
	QGraphicsPolygonItem::hoverLeaveEvent(event);
	event->ignore();
}

void MapViewHexItem::ShowSelected()
{
	setPen( QPen( QBrush(Qt::black), 4 ) );
	update(boundingRect());
}

void MapViewHexItem::ShowOriginal()
{
	setPen( QPen() );
	update(boundingRect());
}
