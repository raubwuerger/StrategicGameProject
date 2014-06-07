#include "stdafx.h"
#include "ProvinceGraphicsPixmapItem.h"
#include "ProvinceItem.h"
#include "ExtendedGraphicsScene.h"

ProvinceGraphicsPixmapItem::ProvinceGraphicsPixmapItem( const QPixmap & pixmapOrg, const QRect& location, ExtendedGraphicsScene *parent )
	: QGraphicsPixmapItem(pixmapOrg),
		m_Location(location),
		m_AttachedProvinceItem(nullptr),
		m_Parent(parent),
		m_OrgPixmap(nullptr)
{
	m_OrgPixmap = new QPixmap(pixmap());
	setAcceptHoverEvents(true);
}

ProvinceGraphicsPixmapItem::ProvinceGraphicsPixmapItem( const ProvinceGraphicsPixmapItem& rhs )
	: QGraphicsPixmapItem(rhs.pixmap()),
	m_Location(rhs.m_Location),
	m_AttachedProvinceItem(rhs.m_AttachedProvinceItem),
	m_Parent(rhs.m_Parent),
	m_OrgPixmap(nullptr)
{
	m_OrgPixmap = new QPixmap(pixmap());
	setOffset( rhs.offset() );
	setAcceptHoverEvents(rhs.acceptHoverEvents());
}

ProvinceGraphicsPixmapItem::~ProvinceGraphicsPixmapItem()
{
	delete m_OrgPixmap;
}

const QRect& ProvinceGraphicsPixmapItem::GetLocation() const 
{ 
	return m_Location; 
}

void ProvinceGraphicsPixmapItem::hoverEnterEvent(QGraphicsSceneHoverEvent * event) 
{
	if( m_Parent != nullptr )
	{
		emit m_Parent->SignalProvinceEntered(m_AttachedProvinceItem);
	}
	ShowSelected();
	QGraphicsPixmapItem::hoverEnterEvent(event);
	event->ignore();
}

void ProvinceGraphicsPixmapItem::hoverLeaveEvent(QGraphicsSceneHoverEvent * event) 
{
	if( m_Parent != nullptr )
	{
		emit m_Parent->SignalProvinceLeft(m_AttachedProvinceItem);
	}
	ShowOriginal();
	QGraphicsPixmapItem::hoverLeaveEvent(event);
	event->ignore();
}

void ProvinceGraphicsPixmapItem::ShowSelected() 
{
//	m_ColorBeforeEnter = 
//	UpdateColor(Qt::black);
}

void ProvinceGraphicsPixmapItem::ShowOriginal() 
{
//	setPixmap( *m_OrgPixmap );

}

const ProvinceItem * ProvinceGraphicsPixmapItem::GetAttachedProvinceItem() const
{
	return m_AttachedProvinceItem;
}

void ProvinceGraphicsPixmapItem::SetAttachedProvinceItem( const ProvinceItem * val )
{
	m_AttachedProvinceItem = val;
}

void ProvinceGraphicsPixmapItem::UpdateColor( const QColor& color )
{
	if( m_OrgPixmap == nullptr )
	{
		return;
	}
	QPixmap pixmap(*m_OrgPixmap);
	pixmap.fill(color);
	pixmap.setMask( m_OrgPixmap->mask() );
	setPixmap( pixmap );
}
