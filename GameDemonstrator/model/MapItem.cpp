#include "stdafx.h"
#include "MapItem.h"

namespace GDModel
{

CMapItem::CMapItem( int row, int col )
	: CenterPoint(0,0),
		Row(row),
		Col(col),
		Type(nullptr),
		Owner(nullptr)
{
}

CMapItem::~CMapItem()
{
}

}