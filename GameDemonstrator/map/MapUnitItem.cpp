#include "stdafx.h"
#include "MapUnitItem.h"

MapUnitItem::MapUnitItem( const QPointF& topLeft )
	: TopLeft(topLeft),
	UnitItemImage(nullptr)
{
	this->setPos(topLeft);
	this->setAcceptHoverEvents(true);
	this->setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton);
	this->setCacheMode(QGraphicsItem::ItemCoordinateCache);
//	this->setZValue(1000); //Be sure to be visible
}

QRectF MapUnitItem::boundingRect() const
{
	return QRectF(QPointF(0,0), QSizeF(64, 43));
}

/** */
void MapUnitItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	if( nullptr != UnitItemImage )
	{
		painter->drawImage(QPointF(0, 0), *UnitItemImage);
	}

	QGraphicsRectItem::paint(painter, option, widget);
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
