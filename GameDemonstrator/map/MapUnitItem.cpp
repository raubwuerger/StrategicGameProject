#include "stdafx.h"
#include "MapUnitItem.h"
#include "connectors\ConnectorMapUnitItem.h"

MapUnitItem::MapUnitItem( const QPointF& topLeft )
	: TopLeft(topLeft),
	UnitItemImage(nullptr),
	EventConnector(nullptr)
{
	ImageRect.setWidth(64);
	ImageRect.setHeight(43);
	this->setPos(topLeft);
	this->setAcceptHoverEvents(true);
	this->setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton);
	this->setCacheMode(QGraphicsItem::ItemCoordinateCache);
	BoundingRect = QRectF(QPointF(0.0, 0.0), ImageRect);
	CreatRect();
	setZValue(255);
}

QRectF MapUnitItem::boundingRect() const
{
	return BoundingRect;
}

void MapUnitItem::hoverEnterEvent(QGraphicsSceneHoverEvent * event)
{
	ShowSelected();
	if (EventConnector != nullptr)
	{
		emit EventConnector->SignalUnitItemEntered(GameUnitId);
	}
	QGraphicsPolygonItem::hoverEnterEvent(event);
	event->ignore();
}

void MapUnitItem::hoverLeaveEvent(QGraphicsSceneHoverEvent * event)
{
	ShowOriginal();
	if (EventConnector != nullptr)
	{
		emit EventConnector->SignalUnitItemLeft(GameUnitId);
	}
	QGraphicsPolygonItem::hoverLeaveEvent(event);
	event->ignore();
}

/** */
void MapUnitItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	if( nullptr != UnitItemImage )
	{
		painter->drawImage(BoundingRect.topLeft(), *UnitItemImage);
	}

	QGraphicsPolygonItem::paint(painter, option, widget);
}

/** Set m_TerrainImage */
void MapUnitItem::SetUnitItemImage(const QImage* val) 
{
	UnitItemImage = val;
}

const QImage* MapUnitItem::GetUnitItemImage() const
{
	return UnitItemImage;
}

void MapUnitItem::SetGameUnitId(int gameUnitId)
{
	GameUnitId = gameUnitId;
}

int MapUnitItem::GetGameUnitId()
{
	return GameUnitId;
}

void MapUnitItem::SetMapHexItemId(int mapHexItemId)
{
	MapHexItemId = mapHexItemId;
}

int MapUnitItem::GetMapHexItemId() const
{
	return MapHexItemId;
}

void MapUnitItem::SetEventConnector(ConnectorMapUnitItem* eventConnector)
{
	EventConnector = eventConnector;
}

void MapUnitItem::ShowSelected()
{
	setPen(QPen(QBrush(Qt::black), 4));
	update(boundingRect());
}

void MapUnitItem::ShowOriginal()
{
	setPen(QPen());
	update(boundingRect());
}

void MapUnitItem::CreatRect()
{
	QPolygonF rectPoints;
	rectPoints << QPointF(0, 0)
		<< QPointF(ImageRect.width(), 0)
		<< QPointF(ImageRect.width(), ImageRect.height())
		<< QPointF(0, ImageRect.height());

	setPolygon(rectPoints);
	setFlags(QGraphicsItem::ItemIsFocusable);
}
