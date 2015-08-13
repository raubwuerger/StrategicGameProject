#include "stdafx.h"
#include "MapViewHexItem.h"

MapViewHexItem::MapViewHexItem(QGraphicsPolygonItem *parent, const int size, const double h)
	: QGraphicsPolygonItem(parent),
	m_Size(size),
	m_Height(h)
{
	QPolygonF polygon;
	polygon << QPointF(2*m_Size,0) << QPointF(m_Size,-m_Height) << QPointF(-m_Size,-m_Height) << QPointF(-2*m_Size,0) << QPointF(-m_Size,m_Height) << QPointF(m_Size,m_Height);
	setPolygon(polygon);
//	setAcceptsHoverEvents(true);
	setFlags(QGraphicsItem::ItemIsFocusable);
}

MapViewHexItem::~MapViewHexItem()
{

}

void MapViewHexItem::paint()
{
	int grass = 20;
	//printf("%d\n",grass);
	setPen(QPen(Qt::black, 0));
	setBrush(QBrush(QColor(255-grass,255,255-grass)));
	update(boundingRect());
}

QRectF MapViewHexItem::boundingRect() const
{
	return QRectF(QPointF(-2 * m_Size,-m_Height),QSizeF(4 * m_Size, 2 * m_Height));
}
