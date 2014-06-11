#include "stdafx.h"
#include "ProvinceGraphicsPixmapItem.h"
#include "ProvinceItem.h"
#include "ExtendedGraphicsScene.h"
#include "std\LogInterface.h"

ProvinceGraphicsPixmapItem::ProvinceGraphicsPixmapItem( const QPixmap & pixmapOrg, const QPixmap & contour, const QRect& location, ExtendedGraphicsScene *parent )
	: QGraphicsPixmapItem(pixmapOrg),
		m_Location(location),
		m_AttachedProvinceItem(nullptr),
		m_Parent(parent),
		m_OrgPixmap(pixmapOrg),
		m_Contour(contour),
		m_ShowContour(false)
{
	setAcceptHoverEvents(true);
}

ProvinceGraphicsPixmapItem::ProvinceGraphicsPixmapItem( const ProvinceGraphicsPixmapItem& rhs )
	: QGraphicsPixmapItem(rhs.pixmap()),
	m_Location(rhs.m_Location),
	m_AttachedProvinceItem(rhs.m_AttachedProvinceItem),
	m_Parent(rhs.m_Parent),
	m_OrgPixmap(rhs.m_OrgPixmap),
	m_Contour(rhs.m_Contour),
	m_ShowContour(rhs.m_ShowContour),
	m_ContourPolygon(rhs.m_ContourPolygon)
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
//	setPixmap( m_Contour );
	setPixmap( ApplyContour(pixmap()) );
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
	if( m_ShowContour == true )
	{
		setPixmap( ApplyContour(pixmap) );
	}
	else
	{
		setPixmap( pixmap );
	}
}

QPixmap ProvinceGraphicsPixmapItem::ApplyContour( const QPixmap& pixmap ) const
{
	QImage image( pixmap.toImage() );
	QPolygon::ConstIterator iter;
	for( iter = m_ContourPolygon.constBegin(); iter != m_ContourPolygon.constEnd(); iter++ )
	{
		image.setPixel((*iter),qRgba(0,0,0,255));
	}
	QPixmap newPixmap;
	newPixmap.convertFromImage(image);
	newPixmap.setMask( pixmap.mask() );
	return newPixmap;
}
