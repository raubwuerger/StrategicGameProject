#include "stdafx.h"
#include "MapViewHexItem.h"

/************************************************************************/
/* MapViewHexItemData                                                   */
/************************************************************************/
HexagonData::HexagonData( double sideLength )
	: SideLength(sideLength),
	Width(0.0),
	Height(0.0),
	Side(0.0)
{
	calcWidth();
	calcHeight();
	calcSide();
	calcBoundingRect();
	calcHexPointsOrigin();
}

void HexagonData::calcWidth()
{
	Width = 2.0 * SideLength;
}

void HexagonData::calcHeight()
{
	Height = sqrt(3) * SideLength;
}

void HexagonData::calcSide()
{
	Side = 3.0 / 2.0 * SideLength;
}

void HexagonData::calcBoundingRect()
{
	BoundingRect = QRectF(QPointF(-Width,-Height),QSizeF(Width, Height));
}

void HexagonData::calcHexPointsOrigin()
{
	HexPoints << QPointF(0,Height*0.5) 
		<< QPointF(Width - Side,0.0) 
		<< QPointF(Side,0.0) 
		<< QPointF(Width,Height*0.5) 
		<< QPointF(Side,Height) 
		<< QPointF(Width - Side,Height);
}

void HexagonData::MovePosition( const QPointF& topLeft )
{
	BoundingRect.moveTopLeft( topLeft );
	HexPoints.translate( topLeft );
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
	TerrainImage(nullptr)
{
	this->data.MovePosition(topLeft);
	this->centerPoint.rx() = topLeft.x() + (data.Width / 2.0);
	this->centerPoint.ry() = topLeft.y() + (data.Height / 2.0);
	
	CreateHexPolygon(this->data);
	setAcceptHoverEvents(true);
	setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton );
}

MapViewHexItem::~MapViewHexItem()
{

}

void MapViewHexItem::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget )
{
	//TODO: Bei Gelegenkeit in eigene Funktion auslagern und nicht permanent ausf�hren lassen
	QRectF textBoundingRect = data.BoundingRect;
	textBoundingRect.setWidth( textBoundingRect.width() * 0.6 );
	textBoundingRect.setHeight( textBoundingRect.height() * 0.2 );
	
	QPointF centerPosText( centerPoint );
	centerPosText.setX( data.BoundingRect.x() + ((data.BoundingRect.width() - textBoundingRect.width()) / 2.0) );
	centerPosText.setY( data.BoundingRect.y() + ((data.BoundingRect.height() - textBoundingRect.height()) / 2.0) );

	textBoundingRect.moveTopLeft( centerPosText );
	
	QTextOption textOption;
	textOption.setAlignment( Qt::AlignHCenter | Qt::AlignVCenter );
	painter->drawText( textBoundingRect, stringRowCol, textOption );

	if( TerrainImage != nullptr )
	{
		painter->drawImage( data.BoundingRect.topLeft(), *TerrainImage );
	}

	QGraphicsPolygonItem::paint(painter,option,widget);
}

QRectF MapViewHexItem::boundingRect() const
{
	return data.BoundingRect;
}

void MapViewHexItem::CreateHexPolygon( const HexagonData &data )
{
	setPolygon(data.HexPoints);
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

void MapViewHexItem::SetTerrainImage( const QImage * val )
{
	TerrainImage = val;
}

/************************************************************************/
/* HexItemEventManager                                                  */
/************************************************************************/
HexItemEventManager::HexItemEventManager()
{

}
