#include "stdafx.h"
#include "MapViewHexItem.h"
#include "HexagonData.h"
#include "HexItemEventManager.h"

/************************************************************************/
/* MapViewHexItem                                                       */
/************************************************************************/
MapViewHexItem::MapViewHexItem( const HexagonData& data, const QPointF& topLeft )
	: HexData(data),
	TopLeftPoint(topLeft),
	Col(-1),
	Row(-1),
	EventItem(nullptr),
	TerrainImage(nullptr)
{
	this->HexData.MovePosition(topLeft);
	this->CenterPoint.rx() = topLeft.x() + (data.Width / 2.0);
	this->CenterPoint.ry() = topLeft.y() + (data.Height / 2.0);
	
	CreateHexPolygon(this->HexData);
	setAcceptHoverEvents(true);
	setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton );
}

MapViewHexItem::~MapViewHexItem()
{

}

void MapViewHexItem::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget )
{
	if( TerrainImage != nullptr )
	{
		painter->drawImage( HexData.BoundingRect.topLeft(), *TerrainImage );
	}

	//TODO: Bei Gelegenkeit in eigene Funktion auslagern und nicht permanent ausführen lassen
	QRectF textBoundingRect = HexData.BoundingRect;
	textBoundingRect.setWidth( textBoundingRect.width() * 0.6 );
	textBoundingRect.setHeight( textBoundingRect.height() * 0.2 );
	
	QPointF centerPosText( CenterPoint );
	centerPosText.setX( HexData.BoundingRect.x() + ((HexData.BoundingRect.width() - textBoundingRect.width()) / 2.0) );
	centerPosText.setY( HexData.BoundingRect.y() + ((HexData.BoundingRect.height() - textBoundingRect.height()) / 2.0) );

	textBoundingRect.moveTopLeft( centerPosText );
	
	QTextOption textOption;
	textOption.setAlignment( Qt::AlignHCenter | Qt::AlignVCenter );
	painter->drawText( textBoundingRect, StringRowCol, textOption );

	QGraphicsPolygonItem::paint(painter,option,widget);
}

QRectF MapViewHexItem::boundingRect() const
{
	return HexData.BoundingRect;
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
	if( EventItem != nullptr )
	{
		emit EventItem->HexItemEntered( Row, Col );
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
	this->Row = row; 
	this->Col = col;

	StringRowCol = QString::number(row) +"|" +QString::number(col);
}

void MapViewHexItem::SetTerrainImage( const QImage * val )
{
	TerrainImage = val;
}
