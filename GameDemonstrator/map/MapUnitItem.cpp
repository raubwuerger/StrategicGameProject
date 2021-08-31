#include "stdafx.h"
#include "MapUnitItem.h"
#include "connectors\ConnectorMapUnitItem.h"
#include "controller\KeyEventController.h"

MapUnitItem::MapUnitItem( const QPointF& topLeft )
	: TopLeft(topLeft),
	UnitItemImage(nullptr),
	EventConnector(nullptr),
	Color(Qt::black),
	BorderWidth(2),
	BorderWidthSelected(4)
{
	ImageRect.setWidth(64);
	ImageRect.setHeight(43);
	this->setPos(topLeft);
	this->setAcceptHoverEvents(true);
	this->setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton);
	this->setCacheMode(QGraphicsItem::ItemCoordinateCache);
	this->setFlags(QGraphicsItem::ItemIsSelectable);
	this->setFlags(QGraphicsItem::ItemIsFocusable);
	BoundingRect = QRectF(QPointF(0.0, 0.0), ImageRect);
	CreatRect();
	setZValue(3);
}

QRectF MapUnitItem::boundingRect() const
{
	return BoundingRect;
}

void MapUnitItem::hoverEnterEvent(QGraphicsSceneHoverEvent * event)
{
	if (EventConnector != nullptr)
	{
		emit EventConnector->SignalUnitItemEntered(GameUnitId);
	}
	QGraphicsPolygonItem::hoverEnterEvent(event);
	event->ignore();
}

void MapUnitItem::hoverLeaveEvent(QGraphicsSceneHoverEvent * event)
{
	if (EventConnector != nullptr)
	{
		emit EventConnector->SignalUnitItemLeft(GameUnitId);
	}
	QGraphicsPolygonItem::hoverLeaveEvent(event);
	event->ignore();
}

void MapUnitItem::keyPressEvent(QKeyEvent * event)
{
	if (nullptr == EventController)
	{
		return;
	}
	EventController->HandleKeyPressEvent(this, event);
}

void MapUnitItem::keyReleaseEvent(QKeyEvent * event)
{
	if (nullptr == EventController)
	{
		return;
	}
	EventController->HandleKeyReleaseEvent(this, event);
}

void MapUnitItem::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
	if (event->button() == Qt::RightButton)
	{
		emit EventConnector->SignalUnitItemPressedRightButton(GameUnitId);
		return;
	}
	if (event->button() == Qt::LeftButton)
	{
		emit EventConnector->SignalUnitItemPressedLeftButton(GameUnitId);
		return;
	}
}

/** */
void MapUnitItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	if( nullptr != UnitItemImage )
	{
		painter->drawImage(BoundingRect.topLeft(), *UnitItemImage);
	}

	this->pen().setColor(Color);
	painter->setRenderHint(QPainter::Antialiasing);
	QPainterPath path;
	path.addRect(BoundingRect);
	painter->setPen(this->pen());
	painter->drawPath(path);
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

int MapUnitItem::GetGameUnitId() const
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

void MapUnitItem::SetKeyEventController(KeyEventController* eventController)
{
	EventController = eventController;
}

void MapUnitItem::ShowSelected()
{
	setPen(QPen(QBrush(Color), BorderWidthSelected));
	update();
}

void MapUnitItem::ShowOriginal()
{
	setPen(QPen(QBrush(Color), BorderWidth));
	update();
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
