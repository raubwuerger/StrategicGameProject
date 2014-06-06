#include "stdafx.h"
#include "ProvinceItem.h"

ProvinceItem::ProvinceItem()
	: QObject(nullptr), 
	m_ID(-1),
	m_Name("prototype"),
	m_Color(Qt::white),
	m_GraphicsItem(nullptr)
{
}


ProvinceItem::ProvinceItem( const ProvinceItem& rhs )
	: QObject(rhs.parent()),
	m_ID(rhs.m_ID),
	m_Name(rhs.m_Name),
	m_Color(rhs.m_Color),
	m_GraphicsItem( rhs.m_GraphicsItem),
	m_Contour(rhs.m_Contour)
{

}

ProvinceItem::ProvinceItem( int id, const QString& name, const QColor& color )
	: QObject(nullptr),
	m_ID(id),
	m_Name(name),
	m_Color(color),
	m_GraphicsItem(nullptr)
{

}

ProvinceItem& ProvinceItem::operator=( const ProvinceItem& rhs )
{
	m_ID = rhs.m_ID;
	m_Name = rhs.m_Name;
	m_Color = rhs.m_Color;
	m_GraphicsItem = rhs.m_GraphicsItem;
	m_Contour = rhs.m_Contour;
	return *this;
}
