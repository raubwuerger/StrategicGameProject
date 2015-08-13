#include "stdafx.h"
#include "MapViewHexItem.h"

MapViewHexItem::MapViewHexItem(QGraphicsPolygonItem *parent, int size, double h)
	: QGraphicsPolygonItem(parent),
	m_Size(size),
	m_Height(h),
	m_BoundingRect(QPointF(-2 * m_Size,-m_Height),QSizeF(4 * m_Size, 2 * m_Height))
{
	QPolygonF polygon;
	polygon << QPointF(2*m_Size,0) << QPointF(m_Size,-m_Height) << QPointF(-m_Size,-m_Height) << QPointF(-2*m_Size,0) << QPointF(-m_Size,m_Height) << QPointF(m_Size,m_Height);
	setPolygon(polygon);
	setFlags(QGraphicsItem::ItemIsFocusable);
}

MapViewHexItem::~MapViewHexItem()
{

}

void MapViewHexItem::paint()
{
	int grass = 20;
	setPen(QPen(Qt::black, 0));
	setBrush(QBrush(QColor(255-grass,255,255-grass)));
	update(boundingRect());
}

QRectF MapViewHexItem::boundingRect() const
{
	return m_BoundingRect;
}
