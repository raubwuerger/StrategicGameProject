#include "stdafx.h"
#include "MapItem.h"

namespace GDModel
{

CMapItem::CMapItem()
	: m_CenterPoint(0,0),
		m_Row(-1),
		m_Col(-1),
		m_Type(nullptr)
{
}

CMapItem::~CMapItem()
{
}

}