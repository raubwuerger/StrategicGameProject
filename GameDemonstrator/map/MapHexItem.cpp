#include "stdafx.h"
#include "MapHexItem.h"
#include "HexagonData.h"
#include "connectors/ConnectorMapHexItem.h"

/************************************************************************/
/* MapViewHexItem                                                       */
/************************************************************************/
MapHexItem::MapHexItem( const HexagonData& data, const QPointF& topLeft )
	: HexData(data),
	TopLeftPoint(topLeft),
	Col(-1),
	Row(-1),
	EventItem(nullptr),
	TerrainImage(nullptr),
	GameMapItemId(-1)
{
	this->HexData.MovePosition(topLeft);
	this->CenterPoint.rx() = topLeft.x() + (data.Width / 2.0);
	this->CenterPoint.ry() = topLeft.y() + (data.Height / 2.0);
	
	CreateHexPolygon(this->HexData);
	setAcceptHoverEvents(true);
	setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton );
	setCacheMode(QGraphicsItem::ItemCoordinateCache);
	setZValue(1);
}

MapHexItem::~MapHexItem()
{

}

void MapHexItem::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget )
{
	//TODO: Die Werte sind für alle Punkte immer gleich. Ausprobieren ob einmal berechnen reicht!
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

int MapHexItem::GetRow() const
{
	return Row;
}

QRectF MapHexItem::boundingRect() const
{
	return HexData.BoundingRect;
}

void MapHexItem::CreateHexPolygon( const HexagonData &data )
{
	setPolygon(data.HexPoints);
	setFlags(QGraphicsItem::ItemIsFocusable);
}

void MapHexItem::hoverEnterEvent(QGraphicsSceneHoverEvent * event) 
{
	ShowSelected();
	if( EventItem != nullptr )
	{
		emit EventItem->SignalHexItemEntered(Row, Col);
	}
	QGraphicsPolygonItem::hoverEnterEvent(event);
	event->ignore();
}

void MapHexItem::hoverLeaveEvent(QGraphicsSceneHoverEvent * event) 
{
	ShowOriginal();
	QGraphicsPolygonItem::hoverLeaveEvent(event);
	event->ignore();
}

void MapHexItem::SetEventConnector(ConnectorMapHexItem * eventConnector)
{
	EventItem = eventConnector;
}

void MapHexItem::ShowSelected()
{
	setPen( QPen( QBrush(Qt::black), 4 ) );
	update(boundingRect());
}

void MapHexItem::ShowOriginal()
{
	setPen( QPen() );
	update(boundingRect());
}

void MapHexItem::SetRowAndCol( int row, int col )
{
	this->Row = row; 
	this->Col = col;

	StringRowCol = QString::number(row) +"|" +QString::number(col);
}

int MapHexItem::GetCol() const
{
	return Col;
}

bool MapHexItem::SetTerrainImage( const QImage * val )
{
	if (nullptr == val)
	{
		return false;
	}
	TerrainImage = val;
	return true;
}

void MapHexItem::SetGameMapItemId(int modelMapItemId)
{
	GameMapItemId = modelMapItemId;
}

int MapHexItem::GetGameMapItemId() const
{
	return GameMapItemId;
}

const QPointF& MapHexItem::GetTopLeftPoint() const
{
	return TopLeftPoint;
}

const QPointF& MapHexItem::GetCenterPoint() const
{
	return CenterPoint;
}
