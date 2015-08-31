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
MapViewHexItem::MapViewHexItem( const HexagonData& data, const QPointF& topLeft, QGraphicsPolygonItem *parent /*= 0*/ )
	: data(data),
	topLeft(topLeft),
	col(-1),
	row(-1),
	eventItem(nullptr),
	m_TerrainImage(nullptr)
{
	this->data.MovePosition(topLeft);
	this->centerPoint.rx() = topLeft.x() + (data.width / 2.0);
	this->centerPoint.ry() = topLeft.y() + (data.height / 2.0);
	
	CreateHexPolygon(this->data);
	setAcceptHoverEvents(true);
	setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton );
}

MapViewHexItem::~MapViewHexItem()
{

}

void MapViewHexItem::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget )
{
	//TODO: Bei Gelegenkeit in eigene Funktion auslagern und nicht permanent ausführen lassen
	QRectF textBoundingRect = data.boundingRect;
	textBoundingRect.setWidth( textBoundingRect.width() * 0.6 );
	textBoundingRect.setHeight( textBoundingRect.height() * 0.2 );
	
	QPointF centerPosText( centerPoint );
	centerPosText.setX( data.boundingRect.x() + ((data.boundingRect.width() - textBoundingRect.width()) / 2.0) );
	centerPosText.setY( data.boundingRect.y() + ((data.boundingRect.height() - textBoundingRect.height()) / 2.0) );

	textBoundingRect.moveTopLeft( centerPosText );
	
	QTextOption textOption;
	textOption.setAlignment( Qt::AlignHCenter | Qt::AlignVCenter );
	painter->drawText( textBoundingRect, stringRowCol, textOption );

	if( m_TerrainImage != nullptr )
	{
		painter->drawImage( data.boundingRect.topLeft(), *m_TerrainImage );
	}

	QGraphicsPolygonItem::paint(painter,option,widget);
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
	setZValue( 255 );
	ShowSelected();
	if( eventItem != nullptr )
	{
		emit eventItem->HexItemEntered( row, col );
	}
	QGraphicsPolygonItem::hoverEnterEvent(event);
	event->ignore();
}

void MapViewHexItem::hoverLeaveEvent(QGraphicsSceneHoverEvent * event) 
{
	setZValue( 0 );
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

void MapViewHexItem::SetRowAndCol( int row, int col )
{
	this->row = row; 
	this->col = col;

	stringRowCol = QString::number(row) +"|" +QString::number(col);
}

void MapViewHexItem::mouseReleaseEvent( QGraphicsSceneMouseEvent * event )
{
	QGraphicsItem::mouseReleaseEvent( event );
}

void MapViewHexItem::mousePressEvent( QGraphicsSceneMouseEvent *event )
{
	QGraphicsItem::mousePressEvent( event );
}
