#include "stdafx.h"
#include "MapItem.h"

namespace GDModel
{

CMapItem::CMapItem( int row, int col )
	: m_CenterPoint(0,0),
		m_Row(row),
		m_Col(col),
		m_Type(nullptr),
		m_Owner(nullptr)
{
}

CMapItem::~CMapItem()
{
}

}