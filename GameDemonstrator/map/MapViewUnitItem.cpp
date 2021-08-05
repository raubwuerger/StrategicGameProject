#include "stdafx.h"
#include "MapViewUnitItem.h"

MapViewUnitItem::MapViewUnitItem() 
	: UnitItemImage(nullptr)
{
}

QRectF MapViewUnitItem::boundingRect() const
{
	return QRectF(QPointF(0,0), QSizeF(64, 43));
}

/** */
void MapViewUnitItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	if( nullptr != UnitItemImage )
	{
		painter->drawImage(QPointF(0, 0), *UnitItemImage);
	}

	QGraphicsRectItem::paint(painter, option, widget);
}

/** Set m_TerrainImage */
void MapViewUnitItem::SetUnitItemImage(const QImage* val) 
{
	UnitItemImage = val;
}
