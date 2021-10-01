#include "stdafx.h"
#include "MapCityItem.h"
#include "connectors/ConnectorMapCityItem.h"
#include "HexagonItem.h"

/************************************************************************/
/* MapViewHexItem                                                       */
/************************************************************************/
MapCityItem::MapCityItem(const QPointF& topLeft, const HexagonItem& hexagonItem)
	: TopLeftPoint(topLeft),
	EventItem(nullptr),
	TerrainImage(nullptr),
	GameMapItemId(-1),
	Hexagon(hexagonItem.GetHexagon())
{
	BoundingRect = QRectF(QPointF(-hexagonItem.GetBoundingRectWidth(), -hexagonItem.GetBoundingRectHeight()), QSizeF(hexagonItem.GetBoundingRectWidth(), hexagonItem.GetBoundingRectHeight()));

	BoundingRect.moveTopLeft(topLeft);
	Hexagon.translate(topLeft);

	this->CenterPoint.rx() = topLeft.x() + (hexagonItem.GetBoundingRectWidth() / 2.0);
	this->CenterPoint.ry() = topLeft.y() + (hexagonItem.GetBoundingRectHeight() / 2.0);
	
	CreateHexPolygon();
	setAcceptHoverEvents(true);
	setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton );
	setCacheMode(QGraphicsItem::ItemCoordinateCache);
	setZValue(2);
}

MapCityItem::~MapCityItem()
{

}

void MapCityItem::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget )
{
	//TODO: Die Werte sind für alle Punkte immer gleich. Ausprobieren ob einmal berechnen reicht!
	if( TerrainImage != nullptr )
	{
		painter->drawImage(this->boundingRect().topLeft(), *TerrainImage);
	}

	//TODO: Bei Gelegenkeit in eigene Funktion auslagern und nicht permanent ausführen lassen
	QRectF textBoundingRect = this->boundingRect();
	textBoundingRect.setWidth( textBoundingRect.width() * 0.6 );
	textBoundingRect.setHeight( textBoundingRect.height() * 0.4 );
	
	QPointF centerPosText( CenterPoint );
	centerPosText.setX(this->boundingRect().x() + ((this->boundingRect().width() - textBoundingRect.width()) / 2.0));
	centerPosText.setY(this->boundingRect().y() + ((this->boundingRect().height() - textBoundingRect.height()) / 2.0));

	textBoundingRect.moveTopLeft( centerPosText );
	
	QTextOption textOption;
	textOption.setAlignment( Qt::AlignHCenter | Qt::AlignVCenter );
	painter->drawText(textBoundingRect, "City", textOption);

	painter->setRenderHint(QPainter::Antialiasing);
	QPainterPath path;
	path.addPolygon(Hexagon);
	QPen pen(Color, 4);
	painter->setPen(pen);
	painter->drawPath(path);
}

void MapCityItem::SetOwnerColor(const QColor ownerColor)
{
	Color = ownerColor;
}

QRectF MapCityItem::boundingRect() const
{
	return BoundingRect;
}

void MapCityItem::CreateHexPolygon()
{
	setPolygon(Hexagon);
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
		emit EventItem->SignalCityItemPressedLeftButton(GameMapItemId);
		return;
	}
	if (event->button() == Qt::RightButton)
	{
		emit EventItem->SignalCityItemPressedRightButton(GameMapItemId);
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

void MapCityItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
	emit EventItem->SignalCityItemDoubleClick(MapCityItemId);
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
