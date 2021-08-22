#include "stdafx.h"
#include "MapCityItem.h"
#include "MapHexItemHexagonData.h"
#include "connectors/ConnectorMapCityItem.h"

/************************************************************************/
/* MapViewHexItem                                                       */
/************************************************************************/
MapCityItem::MapCityItem( const MapHexItemHexagonData& data, const QPointF& topLeft )
	: HexData(data),
	TopLeftPoint(topLeft),
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

MapCityItem::~MapCityItem()
{

}

void MapCityItem::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget )
{
	//TODO: Die Werte sind für alle Punkte immer gleich. Ausprobieren ob einmal berechnen reicht!
	if( TerrainImage != nullptr )
	{
		painter->drawImage( HexData.BoundingRect.topLeft(), *TerrainImage );
	}

	//TODO: Bei Gelegenkeit in eigene Funktion auslagern und nicht permanent ausführen lassen
	QRectF textBoundingRect = HexData.BoundingRect;
	textBoundingRect.setWidth( textBoundingRect.width() * 0.6 );
	textBoundingRect.setHeight( textBoundingRect.height() * 0.4 );
	
	QPointF centerPosText( CenterPoint );
	centerPosText.setX( HexData.BoundingRect.x() + ((HexData.BoundingRect.width() - textBoundingRect.width()) / 2.0) );
	centerPosText.setY( HexData.BoundingRect.y() + ((HexData.BoundingRect.height() - textBoundingRect.height()) / 2.0) );

	textBoundingRect.moveTopLeft( centerPosText );
	
	QTextOption textOption;
	textOption.setAlignment( Qt::AlignHCenter | Qt::AlignVCenter );
	painter->drawText(textBoundingRect, "City", textOption);

	QGraphicsPolygonItem::paint(painter,option,widget);
}

QRectF MapCityItem::boundingRect() const
{
	return HexData.BoundingRect;
}

void MapCityItem::CreateHexPolygon(const MapHexItemHexagonData &data)
{
	setPolygon(data.HexPoints);
	setFlags(QGraphicsItem::ItemIsFocusable);
}

void MapCityItem::hoverEnterEvent(QGraphicsSceneHoverEvent * event) 
{
	ShowSelected();
	emit EventItem->SignalCityItemEntered(MapCityItemId);
	emit EventItem->SignalHexItemEntered(GameMapItemId);
	QGraphicsPolygonItem::hoverEnterEvent(event);
	event->ignore();
}

void MapCityItem::hoverLeaveEvent(QGraphicsSceneHoverEvent * event) 
{
	ShowOriginal();
	QGraphicsPolygonItem::hoverLeaveEvent(event);
	event->ignore();
}

void MapCityItem::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
	if (event->button() == Qt::LeftButton )
	{
//		emit EventItem->SignalHexItemPressedLeftButton(GameMapItemId);
		return;
	}
	if (event->button() == Qt::RightButton)
	{
//		emit EventItem->SignalHexItemPressedRightButton(GameMapItemId);
		return;
	}
}

void MapCityItem::SetEventConnector(ConnectorMapCityItem * eventConnector)
{
	EventItem = eventConnector;
}

void MapCityItem::ShowSelected()
{
	setPen( QPen( QBrush(Qt::black), 4 ) );
	update(boundingRect());
}

void MapCityItem::ShowOriginal()
{
	setPen( QPen() );
	update(boundingRect());
}

void MapCityItem::CreateMapCityItemInfoString()
{
}

bool MapCityItem::SetTerrainImage( const QImage * val )
{
	if (nullptr == val)
	{
		return false;
	}
	TerrainImage = val;
	return true;
}

void MapCityItem::SetGameMapItemId(int modelMapItemId)
{
	GameMapItemId = modelMapItemId;
	CreateMapCityItemInfoString();
}

int MapCityItem::GetGameMapItemId() const
{
	return GameMapItemId;
}

const QPointF& MapCityItem::GetTopLeftPoint() const
{
	return TopLeftPoint;
}

const QPointF& MapCityItem::GetCenterPoint() const
{
	return CenterPoint;
}
