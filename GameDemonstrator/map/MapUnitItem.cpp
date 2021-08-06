#include "stdafx.h"
#include "MapUnitItem.h"

MapUnitItem::MapUnitItem() 
	: UnitItemImage(nullptr)
{
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
