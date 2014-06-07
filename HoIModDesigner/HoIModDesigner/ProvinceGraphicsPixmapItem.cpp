#include "stdafx.h"
#include "ProvinceGraphicsPixmapItem.h"
#include "ProvinceItem.h"
#include "ExtendedGraphicsScene.h"

ProvinceGraphicsPixmapItem::ProvinceGraphicsPixmapItem( const QPixmap & pixmapOrg, const QPixmap & contour, const QRect& location, ExtendedGraphicsScene *parent )
	: QGraphicsPixmapItem(pixmapOrg),
		m_Location(location),
		m_AttachedProvinceItem(nullptr),
		m_Parent(parent),
		m_OrgPixmap(pixmapOrg),
		m_Contour(contour)
{
	setAcceptHoverEvents(true);
}

ProvinceGraphicsPixmapItem::ProvinceGraphicsPixmapItem( const ProvinceGraphicsPixmapItem& rhs )
	: QGraphicsPixmapItem(rhs.pixmap()),
	m_Location(rhs.m_Location),
	m_AttachedProvinceItem(rhs.m_AttachedProvinceItem),
	m_Parent(rhs.m_Parent),
	m_OrgPixmap(rhs.m_OrgPixmap),
	m_Contour(rhs.m_Contour)
{
	setOffset( rhs.offset() );
	setAcceptHoverEvents(rhs.acceptHoverEvents());
}

ProvinceGraphicsPixmapItem::~ProvinceGraphicsPixmapItem()
{
}

const QRect& ProvinceGraphicsPixmapItem::GetLocation() const 
{ 
	return m_Location; 
}

void ProvinceGraphicsPixmapItem::hoverEnterEvent(QGraphicsSceneHoverEvent * event) 
{
	m_LastPixmap = pixmap();
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
	setPixmap(m_LastPixmap);
	QGraphicsPixmapItem::hoverLeaveEvent(event);
	event->ignore();
}

void ProvinceGraphicsPixmapItem::ShowSelected() 
{
	setPixmap( m_Contour );
}

void ProvinceGraphicsPixmapItem::ShowOriginal() 
{
	setPixmap( m_OrgPixmap );
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
	m_LastPixmap = pixmap();
	QPixmap pixmap(pixmap());
	pixmap.fill(color);
	pixmap.setMask( m_OrgPixmap.mask() );
	setPixmap( pixmap );
}
