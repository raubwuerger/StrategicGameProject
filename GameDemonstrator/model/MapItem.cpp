#include "stdafx.h"
#include "MapItem.h"

MapItem::MapItem( int row, int col )
	: CenterPoint(0,0),
		Row(row),
		Col(col),
		Type(nullptr),
		Owner(nullptr)
{
}

MapItem::~MapItem()
{
}
