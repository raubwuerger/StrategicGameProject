#include "stdafx.h"
#include "MapHexItem.h"
#include "MapHexItemHexagonData.h"
#include "connectors/ConnectorMapHexItem.h"

/************************************************************************/
/* MapViewHexItem                                                       */
/************************************************************************/
MapHexItem::MapHexItem( const MapHexItemHexagonData& data, const QPointF& topLeft )
	: HexData(data),
	TopLeftPoint(topLeft),
	Col(-1),
	Row(-1),
	EventItem(nullptr),
	TerrainImage(nullptr),
	GameMapItemId(-1),
	ShowId(true),
	ShowRowAndCol(true),
	ShowCoordinates(false),
	ShowTextBorder(false),
	ShowText(true), 
	DrawHexBorder(true)

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

	ShowTextOnItem(painter);

	if (false == DrawHexBorder)
	{
		return;
	}
	QGraphicsPolygonItem::paint(painter,option,widget);
}

void MapHexItem::ShowTextOnItem(QPainter *painter)
{
	if (false == ShowText)
	{
		return;
	}
	//TODO: Bei Gelegenkeit in eigene Funktion auslagern und nicht permanent ausführen lassen
	QRectF textBoundingRect = HexData.BoundingRect;
	textBoundingRect.setWidth(textBoundingRect.width() * 0.6);
	textBoundingRect.setHeight(textBoundingRect.height() * 0.6);

	QPointF centerPosText(CenterPoint);
	centerPosText.setX(HexData.BoundingRect.x() + ((HexData.BoundingRect.width() - textBoundingRect.width()) / 2.0));
	centerPosText.setY(HexData.BoundingRect.y() + ((HexData.BoundingRect.height() - textBoundingRect.height()) / 2.0));

	textBoundingRect.moveTopLeft(centerPosText);

	QFont font;
	font.setPixelSize(12);

	QTextOption textOption;
	textOption.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	painter->setFont(font);
	painter->drawText(textBoundingRect, MapHexItemInfoString, textOption);
	if (true == ShowTextBorder)
	{
		painter->drawRect(textBoundingRect);
	}
}

int MapHexItem::GetRow() const
{
	return Row;
}

QRectF MapHexItem::boundingRect() const
{
	return HexData.BoundingRect;
}

void MapHexItem::CreateHexPolygon( const MapHexItemHexagonData &data )
{
	setPolygon(data.HexPoints);
	setFlags(QGraphicsItem::ItemIsFocusable);
}

void MapHexItem::hoverEnterEvent(QGraphicsSceneHoverEvent * event) 
{
	ShowSelected();
	emit EventItem->SignalHexItemEntered(GameMapItemId);
	QGraphicsPolygonItem::hoverEnterEvent(event);
	event->ignore();
}

void MapHexItem::hoverLeaveEvent(QGraphicsSceneHoverEvent * event) 
{
	ShowOriginal();
	QGraphicsPolygonItem::hoverLeaveEvent(event);
	event->ignore();
}

void MapHexItem::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
	if (event->button() == Qt::LeftButton )
	{
		emit EventItem->SignalHexItemPressedLeftButton(GameMapItemId);
	}
	if (event->button() == Qt::RightButton)
	{
		emit EventItem->SignalHexItemPressedRightButton(GameMapItemId);
	}
	QGraphicsItem::mousePressEvent(event);
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

void MapHexItem::CreateMapHexItemInfoString()
{
	if (true == ShowRowAndCol)
	{
		MapHexItemInfoString = QString::number(GetRow()) + "|" + QString::number(GetCol());
	}
	
	if (true == ShowId)
	{
		if (false == MapHexItemInfoString.isEmpty())
		{
			MapHexItemInfoString += "\r\n";
		}
		MapHexItemInfoString += "(";
		MapHexItemInfoString += QString::number(GameMapItemId);
		MapHexItemInfoString += ")";
	}

	if (true == ShowCoordinates)
	{
		if (false == MapHexItemInfoString.isEmpty())
		{
			MapHexItemInfoString += "\r\n";
			MapHexItemInfoString += QString::number(TopLeftPoint.x()) + "|" + QString::number(TopLeftPoint.y());
		}
	}
}

void MapHexItem::SetRowAndCol( int row, int col )
{
	this->Row = row; 
	this->Col = col;
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
	CreateMapHexItemInfoString();
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
